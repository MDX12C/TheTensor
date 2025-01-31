#!/bin/bash

cd build
ComMode=""
PS3="Choose the mode:"
select mode in DebugMode NormalMode SpeedMode;
do 
if [ $REPLY -gt 3 ]; then
  echo "undefined mode"
  continue;
fi
if [ $REPLY == 1 ]; then
  ComMode="$ComMode -DdebugMode=ON -DspeedMode=OFF"
elif [ $REPLY == 2 ]; then
  ComMode="$ComMode -DdebugMode=OFF -DspeedMode=OFF"
elif [ $REPLY == 3 ]; then 
  ComMode="$ComMode -DdebugMode=OFF -DspeedMode=ON"
fi
break
done
PS3="Choose the float type:"
select mode in float16 float32;
do
if [ $REPLY -gt 2 ]; then
  echo "undefined type"
  continue;
fi
if [ $REPLY == 1 ]; then
  ComMode="$ComMode -Df16Mode=ON"
else
  ComMode="$ComMode -Df16Mode=OFF"
fi
break
done
cmake $ComMode ..
make