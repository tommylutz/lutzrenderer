#!/bin/sh

GMOCK_GEN=$(find ../../build/ -name 'gmock_gen.py' | head -n1)

for FILE in $(echo *.h | tr ' ' '\n' | grep -v "^mock_"); do
    MOCK="mock_$FILE"
    rm -f $MOCK
        
    INCL_GUARD="_$(echo $MOCK | tr '.' '_' | tr '[:lower:]' '[:upper:]')_"
    echo "#ifndef $INCL_GUARD"          >> $MOCK
    echo "#define $INCL_GUARD"          >> $MOCK
    echo ""                             >> $MOCK
    echo "#include \"$FILE\""           >> $MOCK
    echo "#include \"<gmock/gmock.h>\"" >> $MOCK
    echo ""             >> $MOCK
    $GMOCK_GEN $FILE    >> $MOCK
    echo ""             >> $MOCK
    echo "#endif"       >> $MOCK
    echo ""             >> $MOCK
    echo "Generated mock file $MOCK"
done
