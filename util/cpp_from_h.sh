#!/bin/sh
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
# Name: cpp_from_h.sh
# Desc: A hackish script that will make Haiku-style CPP files from a header
#	file― in the case that you want to make the skeleton of a class'es
#	child.
#	Ended up not using it for the skeleton of ImageControlLook.cpp, but eh.
#	I've already written it, might as well commit. :P
# Date: 2022-06
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――

# If you have garbage in output, this is probably to blame.
only_functions() {
	grep "$(printf '\t')" \
	| grep -v '^[*#/]' \
	| grep -v '^ ' \
	| tr '\t' ' ' \
	| tr -s ' '
}


collapse_functions() {
	local child="$1"
	local parent="$2"

	local OFS="$IFS"
	IFS="
"
	local type=""
	local func=""
	local args=""
	while read line; do
		if echo "$line" | grep '(' > /dev/null; then
			printf '\n\n%s\n%s::%s(%s)\n' "$type" "$child" "$func" "$args" \
			| tr -s ' '

			printf '{\n\t'
			if echo "$type" | grep -v "void" > /dev/null; then
				printf 'return '
			fi
			printf '%s::%s(%s);\n}\n' "$parent" "$func" "$args"

			type="$(echo "$line" | sed 's%(.*%%' | awk '{$(NF--)=""; print}')"
			type="$(echo "$type" | sed 's%virtual %%')"
			func="$(echo "$line" | sed 's%(.*%%' | sed 's%.* %%')"
			args="$(echo "$line" | sed 's%.*(%%' | sed 's%);%%')"
		else
			args="$args $(echo "$line" | sed 's%);%%')"
		fi
	done
	IFS="$OFS"
}


fold_functions() {
	# We swap spaces and commas so that `fold` will wrap on commas
	sed 's%^ %%' \
	| sed 's% %»%g' \
	| sed 's%,% %g' \
	| fold -s --width=98 \
	| sed 's% %,%g' \
	| sed 's%»% %g' \
	| sed 's%^ %\t%' \
	| sed 's%\t %\t\t%' \
	| tr -s ' '
}


FILE="$1"
CHILD="$2"
PARENT="$3"
if test -z "$PARENT" -o -z "$CHILD" -o -z "$FILE"; then
	echo "Usage: $(basename "$0") header_file child_classname parent_classname"
	exit 2
fi


cat "$FILE" \
| only_functions \
| collapse_functions "$CHILD" "$PARENT" \
| fold_functions
