rsync \
	-av \
	--exclude='.svn/' \
	--include='*/' \
	--include='*.c' \
	--include='*.h' \
	--include='LICENSE' \
	--include='Makefile' \
	--exclude='*' \
	~/source/Amy/ \
	~/git/amy/
