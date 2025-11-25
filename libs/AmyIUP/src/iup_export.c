
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

#if 0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "iup.h"
#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_image.h"
#include "iup_func.h"
#include "iup_layout.h"
#include "iup_childtree.h"
#include "iup_array.h"

#endif

static char *iStrGetNoReserved( struct libData *data, const char *p_name )
{
  static char name[128];
  strcpy(name, p_name);
  iupStrReplaceReserved(name, '_');
  return name;
}

static int iExportHasReserved( struct libData *data, const char *name, int check_num )
{
  char c;

  if (*name == 0)  /* empty string must be in quotes */
    return 1;

  c = *name;
  if (check_num && c >= '1' && c <= '9') /* first character can NOT be a number */
    return 1;
  
  while (*name)
  {
    c = *name;

    /* can only has letters or numbers as characters, or underscore */
    if ( c < '0' || 
        (c > '9' && c < 'A') ||
        (c > 'Z' && c < 'a' && c != '_') ||
         c > 'z')
      return 1;

    name++;
  }

  return 0;
}

static void iExportWriteAttrib( struct libData *data, FILE *file, const char *name, const char *value, const char *indent, int export_format )
{
  char attribname[1024];
  const char* old_value = value;
  value = iupStrConvertToC(value);

  if (export_format == IUP_LAYOUT_EXPORT_LUA)  /* Lua */
  {
    iupStrLower(attribname, name);
    if (iExportHasReserved( data, attribname, 1))
      fprintf(file, "%s[\"%s\"] = \"%s\",\n", indent, attribname, value);
    else
      fprintf(file, "%s%s = \"%s\",\n", indent, attribname, value);
  }
  else if (export_format == IUP_LAYOUT_EXPORT_LED) /* LED */
  {
    if (iExportHasReserved( data, name, 0 ))  /* can not be saved in LED */
    {
      if (old_value != value)
        free((char*)value);
      return;
    }

    iupStrUpper(attribname, name);
    if (iExportHasReserved( data, value, 0))
      fprintf(file, "%s=\"%s\", ", attribname, value);
    else
      fprintf(file, "%s=%s, ", attribname, value);
  }
  else   /* C */
    fprintf(file, "%s\"%s\", \"%s\",\n", indent, name, value);

  if (old_value != value)
    free((char*)value);
}

static int iExportCheckAttribExportedInConstructor( struct libData *data, Ihandle *ih, const char *check_name )
{
  const char *format = ih->iclass->format;
  if (!format || format[0] == 0)
    return 0;
  else
  {
    int i, num_format = (int)strlen(format);

    for (i = 0; i < num_format; i++)
    {
      if (format[i] == 's' || format[i] == 'a')
      {
        const char* name = NULL;
        if (i == 0)
          name = ih->iclass->format_attr;
        if (!name)
        {
          if (format[i] == 'a')
            name = "ACTION";
          else
            name = "TITLE";
        }

        if (name && iupStrEqual(name, check_name))
          return 1;
      }
    }

    return 0;
  }
}

static void iExportSavedAttribs( struct libData *data, FILE *file, Ihandle *ih, const char *indent, int export_format )
{
  int i, attr_count;
  char **attr_names;
  char localIndent[1024];
  int wcount = 0;

  strcpy(localIndent, indent);
  strcat(localIndent, "  ");

  attr_count = iupAttribGetAllSaved( data, ih, NULL, 0);
  attr_names = (char **)malloc(attr_count * sizeof(char *));

  attr_count = iupAttribGetAllSaved( data, ih, attr_names, attr_count);
  for (i = 0; i < attr_count; i++)
  {
    if (export_format == IUP_LAYOUT_EXPORT_LED && iExportCheckAttribExportedInConstructor( data, ih, attr_names[i]))
      continue;

    if (export_format != IUP_LAYOUT_EXPORT_LUA || 
        !iupClassObjectAttribIsCallback( data, ih, attr_names[i])) /* do NOT save callbacks in Lua */
    {
      char* value = iupAttribGetLocal( data, ih, attr_names[i]);  /* do NOT check for inherited values */
      if (value)
      {
        iExportWriteAttrib( data, file, attr_names[i], value, localIndent, export_format);
        wcount++;
      }
    }
  }

  if (export_format == IUP_LAYOUT_EXPORT_LED) /* LED */
  {
    if (wcount != 0)
      fseek(file, -2, SEEK_CUR);  /* remove last comma ',' and space */
    else
      fseek(file, -1, SEEK_CUR);/* remove "[" */

    if (wcount != 0)
      fprintf(file, "]"); /* end of attributes (no new line) */
  }

  free(attr_names);
}

static void iExportChangedAttribs( struct libData *data, FILE *file, Ihandle *ih, const char *indent, int export_format )
{
  int i, wcount = 0, attr_count, has_attrib_id = ih->iclass->has_attrib_id, start_id = 0,
    total_count = amy_IupGetClassAttributes( data, ih->iclass->name, NULL, 0);
  char **attr_names = (char **)malloc(total_count * sizeof(char *));

  if (amy_IupClassMatch( data, ih, "tree") || /* tree can only set id attributes after map, so they can not be saved */
      amy_IupClassMatch( data, ih, "cells"))  /* cells does not have any savable id attributes */
    has_attrib_id = 0;

  if (amy_IupClassMatch( data, ih, "list") || amy_IupClassMatch( data, ih, "flatlist"))
    start_id = 1;

  attr_count = amy_IupGetClassAttributes( data, ih->iclass->name, attr_names, total_count);
  for (i = 0; i < attr_count; i++)
  {
    char *name = attr_names[i];
    char* value = iupAttribGetLocal( data, ih, name);  /* do NOT check for inherited values */
    char* def_value;
    int flags;

    iupClassGetAttribNameInfo( data, ih->iclass, name, &def_value, &flags);

    if (value && iupLayoutAttributeHasChanged( data, ih, name, value, def_value, flags))
    {
      char* str = iupStrConvertToC(value);

      iExportWriteAttrib( data, file, name, str, indent, export_format);
      wcount++;

      if (str != value)
        free(str);
    }

    if (has_attrib_id && flags&IUPAF_HAS_ID)
    {
      flags &= ~IUPAF_HAS_ID; /* clear flag so the next function call can work (it will check for read-only, write-only, no-string and no-save) */
      if (iupLayoutAttributeHasChanged( data, ih, name, "XXX", NULL, flags)) /* use a non null and non empty value just to pass the other tests */
      {
        if (iupStrEqual(name, "IDVALUE"))
          name = "";

        if (flags&IUPAF_HAS_ID2)
        {
          int lin, col,
            numcol = amy_IupGetInt( data, ih, "NUMCOL") + 1,
            numlin = amy_IupGetInt( data, ih, "NUMLIN") + 1;
          for (lin = 0; lin < numlin; lin++)
          {
            for (col = 0; col < numcol; col++)
            {
              value = amy_IupGetAttributeId2( data, ih, name, lin, col);
              if (value && value[0] && !iupATTRIB_ISINTERNAL(value))
              {
                char str[50];
                sprintf(str, "%s%d:%d", name, lin, col);
                iExportWriteAttrib( data, file, str, value, indent, export_format);
                wcount++;
              }
            }
          }
        }
        else
        {
          int id, count = amy_IupGetInt( data, ih, "COUNT");
          for (id = start_id; id < count + start_id; id++)
          {
            value = amy_IupGetAttributeId( data, ih, name, id);
            if (value && value[0] && !iupATTRIB_ISINTERNAL(value))
            {
              char str[50];
              sprintf(str, "%s%d", name, id);
              iExportWriteAttrib( data, file, str, value, indent, export_format);
              wcount++;
            }
          }
        }
      }
    }
  }

  if (export_format != IUP_LAYOUT_EXPORT_LUA)  /* LED or C - additional step for callbacks */
  {
    int cb_count = total_count - attr_count;
    amy_IupGetClassCallbacks( data, ih->iclass->name, attr_names, cb_count);
    for (i = 0; i < cb_count; i++)
    {
      char* cb_name = iupGetCallbackName( data, ih, attr_names[i]);
      if (cb_name && cb_name[0] && !iupATTRIB_ISINTERNAL(cb_name))
      {
        iExportWriteAttrib( data, file, attr_names[i], cb_name, indent, export_format);
        wcount++;
      }
    }
  }

  if (export_format == IUP_LAYOUT_EXPORT_LED ) /* LED */
  {
    if (wcount != 0)
      fseek(file, -2, SEEK_CUR);  /* remove last comma ',' and space */
    else
      fseek(file, -1, SEEK_CUR);/* remove "[" */

    if (wcount != 0)
      fprintf(file, "]"); /* end of attributes (no new line) */
  }

  free(attr_names);
}

static char* iExportGetName( struct libData *data, Ihandle *ih )
{
  char* name = amy_IupGetName( data, ih );
  if (name && iupATTRIB_ISINTERNAL(name))
    name = NULL;
  return name;
}

static void iExportElementLED( struct libData *data, FILE *file, Ihandle *ih, const char *indent, int saved_info )
{
  int i, count;
  const char* format = ih->iclass->format;
  char classname[100];

  char* name = iExportGetName( data, ih );

  iupStrUpper(classname, ih->iclass->name);
  if (name)
    fprintf(file, "%s = %s[", iStrGetNoReserved( data, name ), classname);  /* start of attributes */
  else
    fprintf(file, "%s%s[", indent, classname);

  if (saved_info)
    iExportSavedAttribs( data, file, ih, indent, IUP_LAYOUT_EXPORT_LED);
  else
    iExportChangedAttribs( data, file, ih, indent, IUP_LAYOUT_EXPORT_LED);

  if (!format || format[0] == 0)
    fprintf(file, "()");
  else
  {
    if (*format == 'g')  /* a multi child container (can only has 1 format) */
    {
      Ihandle *child;
      char localIndent[1024];

      strcpy(localIndent, indent);
      strcat(localIndent, "  ");

      fprintf(file, "(\n");

      if (ih->iclass->childtype == IUP_CHILDNONE) /* amy_IupNormalizer exception */
      {
        child = (Ihandle*)amy_IupGetAttribute( data, ih, "FIRST_CONTROL_HANDLE");
        while (child)
        {
          if (!(child->flags & IUP_INTERNAL))
          {
            char* childname = iExportGetName( data, child );
            if (!childname)
              iExportElementLED( data, file, child, localIndent, saved_info);   /* here process the ones that does NOT have names */
            else
              fprintf(file, "%s%s", localIndent, childname);

            child = (Ihandle*)amy_IupGetAttribute( data, ih, "NEXT_CONTROL_HANDLE");

            if (child)
              fprintf(file, ",\n");
          }
          else
            child = (Ihandle*)amy_IupGetAttribute( data, ih, "NEXT_CONTROL_HANDLE");
        }
      }
      else
      {
        for (child = ih->firstchild; child; child = child->brother)
        {
          if (!(child->flags & IUP_INTERNAL))
          {
            char* childname = iExportGetName( data, child);
            if (!childname)
              iExportElementLED( data, file, child, localIndent, saved_info);   /* here process the ones that does NOT have names */
            else
              fprintf(file, "%s%s", localIndent, childname);

            if (child->brother)
              fprintf(file, ",\n");
          }
        }
      }

      fprintf(file, "\n%s)", indent);
    }
    else
    {
      count = (int)strlen(format);

      fprintf(file, "(");

      for (i = 0; i < count; i++)
      {
        if (format[i] == 's')
        {
          char* value;
          const char* attribname = NULL;
          if (i == 0)
            attribname = ih->iclass->format_attr;
          if (!attribname)
            attribname = "TITLE";

          value = iupAttribGetLocal( data, ih, attribname);  /* do NOT check for inherited values */
          if (value)
            fprintf(file, "\"%s\"", value); /* always with quotes in constructor */
          else
            fprintf(file, "\"\"");  /* empty string */
        }
        else if (format[i] == 'a')
        {
          char* cb_name = NULL;
          if (i == 0 && ih->iclass->format_attr)
            cb_name = iupGetCallbackName( data, ih, ih->iclass->format_attr);
          if (!cb_name)
            cb_name = iupGetCallbackName( data, ih, "ACTION");

          if (cb_name && cb_name[0] && !iupATTRIB_ISINTERNAL(cb_name))
            fprintf(file, "%s", cb_name);
          else
            fprintf(file, "do_nothing");  /* dummy name */
        }
        else if (format[i] == 'h')
        {
          Ihandle *child;

          if (ih->iclass->childtype == IUP_CHILDNONE)  /* amy_IupAnimatedLabel and amy_IupDropButton exceptions */
          {
            child = (Ihandle*)amy_IupGetAttribute( data, ih, "FIRST_CONTROL_HANDLE");
            while (child)
            {
              if (!(child->flags & IUP_INTERNAL))
              {
                char* childname = iExportGetName( data, child );
                if (!childname)
                {
                  char localIndent[1024];

                  strcpy(localIndent, indent);
                  strcat(localIndent, "  ");

                  fprintf(file, "\n");
                  iExportElementLED( data, file, child, localIndent, saved_info);   /* here process the ones that does NOT have names */
                }
                else
                  fprintf(file, "%s", childname);

                break; /* only one child */
              }

              child = (Ihandle*)amy_IupGetAttribute( data, ih, "NEXT_CONTROL_HANDLE");
            }
          }
          else
          {
            for (child = ih->firstchild; child; child = child->brother)
            {
              if (!(child->flags & IUP_INTERNAL))
              {
                char* childname = iExportGetName( data, child );
                if (!childname)
                {
                  char localIndent[1024];

                  strcpy(localIndent, indent);
                  strcat(localIndent, "  ");

                  fprintf(file, "\n");
                  iExportElementLED( data, file, child, localIndent, saved_info);   /* here process the ones that does NOT have names */
                }
                else
                  fprintf(file, "%s", childname);

                break; /* only one child */
              }
            }
          }
        }

        if (i != count - 1)
          fprintf(file, ", ");
      }

      fprintf(file, ")");
    }
  }

  if (name)
    fprintf(file, "\n\n");
}

static void iExportElementLua( struct libData *data, FILE *file, Ihandle *ih, const char *indent, int saved_info )
{
  Ihandle *child;
  char* name = iExportGetName( data, ih );

  if (name)
    fprintf(file, "%s_lc.%s = ", indent, iStrGetNoReserved( data, name ));
  else
    fprintf(file, "%s", indent);

  fprintf(file, "iup.%s{\n", ih->iclass->name);

  if (ih->iclass->childtype != IUP_CHILDNONE)
  {
    char localIndent[1024];

    strcpy(localIndent, indent);
    strcat(localIndent, "  ");

    for (child = ih->firstchild; child; child = child->brother)
    {
      char* childName = iExportGetName( data, child );
      if (childName)
      {
        if (iupAttribGet( data, child, "_IUP_EXPORT_LUA_SAVED")) /* saved in the same scope */
          fprintf(file, "%s_lc.%s,\n", localIndent, childName);
        else
          fprintf(file, "%siup.GetHandle(\"%s\"),\n", localIndent, childName);
      }
      else
      {
        iExportElementLua( data, file, child, localIndent, saved_info);
        fprintf(file, ",\n");
      }
    }
  }
  else  /* childtype == IUP_CHILDNONE */
  {
    if (ih->iclass->format && (ih->iclass->format[0] == 'h' ||  /* amy_IupAnimatedLabel and amy_IupDropButton exceptions */
                               ih->iclass->format[0] == 'g'))    /* amy_IupNormalizer exception */
    {
      char localIndent[1024];

      strcpy(localIndent, indent);
      strcat(localIndent, "  ");

      child = (Ihandle*)amy_IupGetAttribute( data, ih, "FIRST_CONTROL_HANDLE");
      while (child)
      {
        char* childName = iExportGetName( data, child );
        if (childName)
        {
          if (iupAttribGet( data, child, "_IUP_EXPORT_LUA_SAVED")) /* saved in the same scope */
            fprintf(file, "%s_lc.%s,\n", localIndent, childName);
          else
            fprintf(file, "%siup.GetHandle(\"%s\"),\n", localIndent, childName);
        }
        else
        {
          iExportElementLua( data, file, child, localIndent, saved_info);
          fprintf(file, ",\n");
        }

        child = (Ihandle*)amy_IupGetAttribute( data, ih, "NEXT_CONTROL_HANDLE");
      }
    }
  }

  if (saved_info)
    iExportSavedAttribs( data, file, ih, indent, IUP_LAYOUT_EXPORT_LUA);
  else
    iExportChangedAttribs( data, file, ih, indent, IUP_LAYOUT_EXPORT_LUA);

  fprintf(file, "%s}", indent);
}

static void iExportElementC( struct libData *data, FILE *file, Ihandle *ih, const char *indent, const char *terminator, int saved_info )
{
  char* name = iExportGetName( data, ih );

  if (ih->iclass->childtype != IUP_CHILDNONE)
  {
    Ihandle *child;
    char localIndent[1024];

    if (name)
      fprintf(file, "%samy_IupSetAtt(\"%s\", amy_IupCreatep(\"%s\", \n", indent, name, ih->iclass->name);
    else
      fprintf(file, "%samy_IupSetAtt(NULL, amy_IupCreatep(\"%s\", \n", indent, ih->iclass->name);

    strcpy(localIndent, indent);
    strcat(localIndent, "    ");  /* indent twice for children */

    for (child = ih->firstchild; child; child = child->brother)
    {
      char* childName = iExportGetName( data, child );
      if (childName)
        fprintf(file, "%samy_IupGetHandle(\"%s\"),\n", localIndent, childName);
      else 
        iExportElementC( data, file, child, localIndent, ",", saved_info); /* no ; */
    }

    fprintf(file, "%sNULL),\n", localIndent);  /* amy_IupCreatep */
  }
  else /* childtype == IUP_CHILDNONE */
  {
    if (ih->iclass->format && (ih->iclass->format[0] == 'h' ||  /* amy_IupAnimatedLabel and amy_IupDropButton exceptions */
                               ih->iclass->format[0] == 'g'))    /* amy_IupNormalizer exception */
    {
      Ihandle *child;
      char localIndent[1024];

      if (name)
        fprintf(file, "%samy_IupSetAtt(\"%s\", amy_IupCreatep(\"%s\", \n", indent, name, ih->iclass->name);
      else
        fprintf(file, "%samy_IupSetAtt(NULL, amy_IupCreatep(\"%s\", \n", indent, ih->iclass->name);

      strcpy(localIndent, indent);
      strcat(localIndent, "  ");

      child = (Ihandle*)amy_IupGetAttribute( data, ih, "FIRST_CONTROL_HANDLE");
      while (child)
      {
        char* childName = iExportGetName( data, child );
        if (childName)
          fprintf(file, "%samy_IupGetHandle(\"%s\"),\n", localIndent, childName);
        else
          iExportElementC( data, file, child, localIndent, ",", saved_info); /* no ; */

        child = (Ihandle*)amy_IupGetAttribute( data, ih, "NEXT_CONTROL_HANDLE");
      }

      fprintf(file, "%sNULL),\n", localIndent);  /* amy_IupCreatep */
    }
    else
    {
      if (name)
        fprintf(file, "%samy_IupSetAtt(\"%s\", amy_IupCreate(\"%s\"), \n", indent, name, ih->iclass->name);
      else
        fprintf(file, "%samy_IupSetAtt(NULL, amy_IupCreate(\"%s\"), \n", indent, ih->iclass->name);
    }
  }

  if (saved_info)
    iExportSavedAttribs( data, file, ih, indent, IUP_LAYOUT_EXPORT_C);
  else
    iExportChangedAttribs( data, file, ih, indent, IUP_LAYOUT_EXPORT_C);

  fprintf(file, "%s  NULL)%s\n", indent, terminator);  /* amy_IupSetAtt */

  if (terminator[0] == ';')
    fprintf(file, "\n");
}

IUP_SDK_API void iupLayoutExportNamedElemList( struct libData *data, FILE *file, Ihandle* *named_elem, int count, int export_format, int saved_info )
{
  int i, first = 1;
  Ihandle *elem;

  for (i = 0; i < count; i++)
  {
    elem = named_elem[i];

    if (elem->iclass->nativetype != IUP_TYPEIMAGE)
    {
      char* name = amy_IupGetName( data, elem );

      if (export_format == IUP_LAYOUT_EXPORT_LUA)
      {
        if (first)
        {
          fprintf(file, "  local _lc = {}\n\n"); /* use a single local variable to avoid the 200 limit in Lua */
          first = 0;
        }

        iExportElementLua( data, file, elem, "  ", saved_info);
        fprintf(file, "\n");
      }
      else if (export_format == IUP_LAYOUT_EXPORT_C)
        iExportElementC( data, file, elem, "  ", ";", saved_info);
      else
        iExportElementLED( data, file, elem, "  ", saved_info);

      if (export_format == IUP_LAYOUT_EXPORT_LUA && name)
      {
        fprintf(file, "  iup.SetHandle(\"%s\", _lc.%s)\n\n", name, iStrGetNoReserved( data, name ));
        iupAttribSet( data, elem, "_IUP_EXPORT_LUA_SAVED", "1");
      }
    }
  }

  if (export_format == IUP_LAYOUT_EXPORT_LUA)
  {
    for (i = 0; i < count; i++)
    {
      elem = named_elem[i];
      if (amy_IupGetName( data, elem ))
        iupAttribSet( data, elem, "_IUP_EXPORT_LUA_SAVED", NULL );
    }
  }
}

IUP_SDK_API void iupLayoutExportNamedImageList( struct libData *data, FILE *file, Ihandle* *named_elem, int count, int export_format )
{
  int i;
  Ihandle *elem;

  for (i = 0; i < count; i++)
  {
    elem = named_elem[i];

    if (elem->iclass->nativetype == IUP_TYPEIMAGE)
    {
      char* format[] = { "LUA", "C", "LED" };
      char* name = amy_IupGetName( data, elem );

      iupImageExportToFile( data, elem, file, format[export_format], name);

      if (export_format == IUP_LAYOUT_EXPORT_LUA && name)
        iupAttribSet( data, elem, "_IUP_EXPORT_LUA_SAVED", "1");
    }
  }
}

IUP_SDK_API void iupLayoutExportNamedImageListSetHandle( struct libData *data, FILE *file, Ihandle* *named_elem, int count, int export_format )
{
  int i;
  Ihandle *elem;

  if (export_format == IUP_LAYOUT_EXPORT_LUA || export_format == IUP_LAYOUT_EXPORT_C)
  {
    for (i = 0; i < count; i++)
    {
      elem = named_elem[i];

      if (elem->iclass->nativetype == IUP_TYPEIMAGE)
      {
        char* name = amy_IupGetName( data, elem );
        if (name)
        {
          if (export_format == IUP_LAYOUT_EXPORT_LUA)
            fprintf(file, "  iup.SetHandle(\"%s\", create_image_%s())\n", name, iStrGetNoReserved( data, name ));
          else
            fprintf(file, "  amy_IupSetHandle(\"%s\", create_image_%s());\n", name, iStrGetNoReserved( data, name ));
        }
      }
    }
  }
}


/******************************************************************************/


static int iExportImagePrintBuffer( struct libData *data, Iarray *buffer, const char *format, va_list arglist )
{
  char str[100];
  int count, len;
  char *data2;

  count = iupArrayCount( data, buffer );

  len = vsprintf(str, format, arglist);

  if (len < 0)
    return len;

  iupArrayAdd( data, buffer, len );

  data2 = (char*)iupArrayGetData( data, buffer );

  memcpy( data2 + count, str, len);

  return len;
}

static int iExportImagePrint( struct libData *data, FILE *file, Iarray *buffer, char *format, ... )
{
  int len;
  va_list arglist;
  va_start(arglist, format);

  if (file)
    len = vfprintf(file, format, arglist);
  else
    len = iExportImagePrintBuffer( data, buffer, format, arglist);

  va_end(arglist);

  return len;
}

static int iExportSaveImageC( struct libData *data, const char *filename, Ihandle *ih, const char *name, FILE *packfile, Iarray *buffer )
{
  int y, x, width, height, channels, linesize;
  unsigned char* data2;
  FILE* file = NULL;

  data2 = (unsigned char*)iupAttribGet( data, ih, "WID");
  if (!data2)
    return 0;

  if (packfile)
    file = packfile;
  else if (filename)
    file = fopen(filename, "wb");

  if (!file && !buffer)
    return 0;

  width = amy_IupGetInt( data, ih, "WIDTH");
  height = amy_IupGetInt( data, ih, "HEIGHT");
  channels = amy_IupGetInt( data, ih, "CHANNELS");
  linesize = width * channels;

  if (iExportImagePrint( data, file, buffer, "static Ihandle* create_image_%s(void)\n", name) < 0)
  {
    if (filename)
      fclose(file);
    return 0;
  }
  iExportImagePrint( data, file, buffer, "{\n");

  if (amy_IupGetInt( data, NULL, "IMAGEEXPORT_STATIC"))
    iExportImagePrint( data, file, buffer, "  static unsigned char imgdata[] = {\n");
  else
    iExportImagePrint( data, file, buffer, "  unsigned char imgdata[] = {\n");

  for (y = 0; y < height; y++)
  {
    iExportImagePrint( data, file, buffer, "    ");

    for (x = 0; x < linesize; x++)
    {
      if (x != 0)
        iExportImagePrint( data, file, buffer, ", ");

      iExportImagePrint( data, file, buffer, "%d", (int)data2[y*linesize + x]);
    }

    if (y == height - 1)
      iExportImagePrint( data, file, buffer, "};\n\n");
    else
      iExportImagePrint( data, file, buffer, ",\n");
  }

  if (channels == 1)
  {
    int c;
    char* color;

    iExportImagePrint( data, file, buffer, "  Ihandle* image = amy_IupImage(%d, %d, imgdata);\n\n", width, height);

    for (c = 0; c < 256; c++)
    {
      color = amy_IupGetAttributeId( data, ih, "", c);
      if (!color)
        break;

      iExportImagePrint( data, file, buffer, "  amy_IupSetAttribute(image, \"%d\", \"%s\");\n", c, color);
    }

    iExportImagePrint( data, file, buffer, "\n");
  }
  else if (channels == 3)
    iExportImagePrint( data, file, buffer, "  Ihandle* image = amy_IupImageRGB(%d, %d, imgdata);\n", width, height);
  else /* channels == 4 */
    iExportImagePrint( data, file, buffer, "  Ihandle* image = amy_IupImageRGBA(%d, %d, imgdata);\n", width, height);

  iExportImagePrint( data, file, buffer, "  return image;\n");

  iExportImagePrint( data, file, buffer, "}\n\n");

  if (filename)
    fclose(file);

  return 1;
}

static int iExportSaveImageLua( struct libData *data, const char *filename, Ihandle *ih, const char *name, FILE *packfile, Iarray *buffer )
{
  int y, x, width, height, channels, linesize;
  unsigned char* data2;
  FILE* file = NULL;

  data2 = (unsigned char*)iupAttribGet( data, ih, "WID");
  if (!data2)
    return 0;

  if (packfile)
    file = packfile;
  else if (filename)
    file = fopen(filename, "wb");

  if (!file && !buffer)
    return 0;

  width = amy_IupGetInt( data, ih, "WIDTH");
  height = amy_IupGetInt( data, ih, "HEIGHT");
  channels = amy_IupGetInt( data, ih, "CHANNELS");
  linesize = width * channels;

  if (iExportImagePrint( data, file, buffer, "function create_image_%s()\n", name) < 0)
  {
    if (!packfile)
      fclose(file);
    return 0;
  }

  if (channels == 1)
    iExportImagePrint( data, file, buffer, "  local %s = iup.image{\n", name);
  else if (channels == 3)
    iExportImagePrint( data, file, buffer, "  local %s = iup.imagergb{\n", name);
  else /* channels == 4 */
    iExportImagePrint( data, file, buffer, "  local %s = iup.imagergba{\n", name);

  iExportImagePrint( data, file, buffer, "    width = %d,\n", width);
  iExportImagePrint( data, file, buffer, "    height = %d,\n", height);
  iExportImagePrint( data, file, buffer, "    pixels = {\n");

  for (y = 0; y < height; y++)
  {
    iExportImagePrint( data, file, buffer, "      ");
    for (x = 0; x < linesize; x++)
    {
      iExportImagePrint( data, file, buffer, "%d, ", (int)data2[y*linesize + x]);
    }
    iExportImagePrint( data, file, buffer, "\n");
  }

  iExportImagePrint( data, file, buffer, "    },\n");

  if (channels == 1)
  {
    int c;
    char* color;
    unsigned char r, g, b;

    iExportImagePrint( data, file, buffer, "    colors = {\n");

    for (c = 0; c < 256; c++)
    {
      color = amy_IupGetAttributeId( data, ih, "", c);
      if (!color)
        break;

      /* don't use index, this Lua constructor assumes index=0 the first item in the array */
      if (iupStrEqualNoCase(color, "BGCOLOR"))
        iExportImagePrint( data, file, buffer, "      \"BGCOLOR\",\n"); 
      else
      {
        iupStrToRGB(color, &r, &g, &b);
        iExportImagePrint( data, file, buffer, "      \"%d %d %d\",\n", (int)r, (int)g, (int)b);
      }
    }

    iExportImagePrint( data, file, buffer, "    }\n");
  }

  iExportImagePrint( data, file, buffer, "  }\n");

  iExportImagePrint( data, file, buffer, "  return %s\n", name);
  iExportImagePrint( data, file, buffer, "end\n\n");

  if (filename)
    fclose(file);

  return 1;
}

static int iExportSaveImageLED( struct libData *data, const char *filename, Ihandle *ih, const char *name, FILE *packfile, Iarray *buffer )
{
  int y, x, width, height, channels, linesize;
  unsigned char* data2;
  FILE* file = NULL;

  data2 = (unsigned char*)iupAttribGet( data, ih, "WID");
  if (!data2)
    return 0;

  if (packfile)
    file = packfile;
  else if (filename)
    file = fopen(filename, "wb");

  if (!file && !buffer)
    return 0;

  width = amy_IupGetInt( data, ih, "WIDTH");
  height = amy_IupGetInt( data, ih, "HEIGHT");
  channels = amy_IupGetInt( data, ih, "CHANNELS");
  linesize = width * channels;

  if (channels == 1)
  {
    int c;
    unsigned char r, g, b;
    char* color;

    if (iExportImagePrint( data, file, buffer, "%s = IMAGE[\n", name) < 0)
    {
      if (filename)
        fclose(file);
      return 0;
    }

    for (c = 0; c < 256; c++)
    {
      color = amy_IupGetAttributeId( data, ih, "", c);
      if (!color)
      {
        if (c < 16)
          continue;
        else
          break;
      }

      if (c != 0)
        iExportImagePrint( data, file, buffer, ",\n");

      if (iupStrEqualNoCase(color, "BGCOLOR"))
        iExportImagePrint( data, file, buffer, "  %d = \"BGCOLOR\"", c);
      else
      {
        iupStrToRGB(color, &r, &g, &b);
        iExportImagePrint( data, file, buffer, "  %d = \"%d %d %d\"", c, (int)r, (int)g, (int)b);
      }
    }
    iExportImagePrint( data, file, buffer, "]\n  ");
  }
  else if (channels == 3)
  {
    if (iExportImagePrint( data, file, buffer, "%s = IMAGERGB", name) < 0)
    {
      if (filename)
        fclose(file);
      return 0;
    }
  }
  else /* channels == 4 */
  {
    if (iExportImagePrint( data, file, buffer, "%s = IMAGERGBA", name) < 0)
    {
      if (filename)
        fclose(file);
      return 0;
    }
  }

  iExportImagePrint( data, file, buffer, "(%d, %d,\n", width, height);

  for (y = 0; y < height; y++)
  {
    iExportImagePrint( data, file, buffer, "  ");
    for (x = 0; x < linesize; x++)
    {
      if (y == height - 1 && x == linesize - 1)
        iExportImagePrint( data, file, buffer, "%d", (int)data2[y*linesize + x]);
      else
        iExportImagePrint( data, file, buffer, "%d, ", (int)data2[y*linesize + x]);
    }
    iExportImagePrint( data, file, buffer, "\n");
  }

  iExportImagePrint( data, file, buffer, ")\n\n");

  if (filename)
    fclose(file);

  return 1;
}

IUP_API int amy_IupSaveImageAsText( struct libData *data, Ihandle *ih, const char *filename, const char *format, const char *p_name )
{
  int ret = 0;
  char name[128];

  if (!p_name)
  {
    p_name = amy_IupGetName( data, ih );
    if (!p_name)
      p_name = "image";
  }

  strcpy(name, p_name);
  iupStrReplaceReserved(name, '_');

  if (iupStrEqualNoCase(format, "LED"))
    ret = iExportSaveImageLED( data, filename, ih, name, NULL, NULL);
  else if (iupStrEqualNoCase(format, "LUA"))
    ret = iExportSaveImageLua( data, filename, ih, name, NULL, NULL);
  else if (iupStrEqualNoCase(format, "C"))
    ret = iExportSaveImageC( data, filename, ih, name, NULL, NULL);
  return ret;
}

IUP_SDK_API int iupImageExportToFile( struct libData *data, Ihandle *ih, FILE *packfile, const char *format, const char *p_name )
{
  int ret = 0;
  char name[128];

  if (!p_name)
  {
    p_name = amy_IupGetName( data, ih );
    if (!p_name)
      p_name = "image";
  }

  strcpy(name, p_name);
  iupStrReplaceReserved(name, '_');

  if (iupStrEqualNoCase(format, "LED"))
    ret = iExportSaveImageLED( data, NULL, ih, name, packfile, NULL);
  else if (iupStrEqualNoCase(format, "LUA"))
    ret = iExportSaveImageLua( data, NULL, ih, name, packfile, NULL);
  else if (iupStrEqualNoCase(format, "C"))
    ret = iExportSaveImageC( data, NULL, ih, name, packfile, NULL);
  return ret;
}

IUP_SDK_API int iupImageExportToString( struct libData *data, Ihandle *ih, char **str, const char *format, const char *p_name )
{
  Iarray *buffer = iupArrayCreate( data, 1024, sizeof(char));
  int ret = 0, count;
  char name[128];

  if (!p_name)
  {
    p_name = amy_IupGetName( data, ih );
    if (!p_name)
      p_name = "image";
  }

  strcpy(name, p_name);
  iupStrReplaceReserved(name, '_');

  if (iupStrEqualNoCase(format, "LED"))
    ret = iExportSaveImageLED( data, NULL, ih, name, NULL, buffer);
  else if (iupStrEqualNoCase(format, "LUA"))
    ret = iExportSaveImageLua( data, NULL, ih, name, NULL, buffer);
  else if (iupStrEqualNoCase(format, "C"))
    ret = iExportSaveImageC( data, NULL, ih, name, NULL, buffer);

  count = iupArrayCount( data, buffer );
  *str = iupArrayInc( data, buffer );
  (*str)[count] = 0;

  *str = iupArrayReleaseData( data, buffer );

  iupArrayDestroy( data, buffer );

  return ret;
}

