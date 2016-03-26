#!/bin/sh

WORKDIR=$1
if [ -z "$WORKDIR" ]; then
    echo "Bad folder specified"
    exit 1
fi

GMOCK_GEN=$(find $WORKDIR/../../build/ -name 'gmock_gen.py' | head -n1)

find $WORKDIR/ -name 'mock_*.h' -exec rm {} \;

for FILE in $(find $WORKDIR/ -name '*.h' | grep -v "^mock_"); do
    MOCK="$WORKDIR/mock_$(basename $FILE)"
    rm -f $MOCK
        
    INCL_GUARD="_$(echo $(basename "$MOCK") | tr '.' '_' | tr '[:lower:]' '[:upper:]')_"
    echo "#ifndef $INCL_GUARD"          >> $MOCK
    echo "#define $INCL_GUARD"          >> $MOCK
    echo ""                             >> $MOCK
    echo "#include \"$(basename $FILE)\""           >> $MOCK
    #Whoever includes this mock interface MUST include gmock.h first
    #echo "#include \"<gmock/gmock.h>\"" >> $MOCK
    echo ""             >> $MOCK
    $GMOCK_GEN $FILE    >> $MOCK
    echo ""             >> $MOCK
    echo "#endif"       >> $MOCK
    echo ""             >> $MOCK
    echo "Generated mock file $MOCK"
done
