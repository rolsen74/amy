rsync \
	-av \
	--exclude='.svn/' \
	--include='*/' \
	--include='*.c' \
	--include='*.h' \
	--include='LICENSE' \
	--include='Makefile' \
	--include='.vscode/' \
	--include='.vscode/*.json' \
	--exclude='*' \
	~/source/Amy/ \
	~/git/amy/
