#!/bin/bash

cd build
ComMode=""
PS3="Open Speed mode?:"
select mode in OFF ON;
do 
if [ $REPLY -gt 2 ]; then
  echo "undefined mode"
  continue;
fi
if [ $REPLY == 2 ]; then
  ComMode="$ComMode -DspeedMode=ON"
else
  ComMode="$ComMode -DspeedMode=OFF"
fi
break
done
PS3="Choose the float type:"
select mode in float32 float16;
do
if [ $REPLY -gt 2 ]; then
  echo "undefined type"
  continue;
fi
if [ $REPLY == 2 ]; then
  ComMode="$ComMode -Df16Mode=ON"
else
  ComMode="$ComMode -Df16Mode=OFF"
fi
break
done
PS3="Open Debug Mode:"
select mode in OFF ON
do
if [ $REPLY -gt 2 ]; then
  echo "undefined mode"
  continue;
fi
if [ $REPLY == 1 ]; then 
  ComMode="$ComMode -DdebugMode=OFF"
else
  ComMode="$ComMode -DdebugMode=ON"
fi
break
done
PS3="Open Limit Mode:"
select mode in OFF ON
do
if [ $REPLY -gt 2 ]; then
  echo "undefined mode"
  continue;
fi
if [ $REPLY == 1 ]; then 
  ComMode="$ComMode -DlimitMode=OFF"
else
  ComMode="$ComMode -DlimitMode=ON"
fi
break
done
PS3="Open Cuda:"
select mode in OFF ON
do
if [ $REPLY -gt 2 ]; then
  echo "undefined mode"
  continue;
fi
if [ $REPLY == 1 ]; then 
  ComMode="$ComMode -DcudaMode=OFF"
else
  ComMode="$ComMode -DcudaMode=ON"
fi
break
done
cmake $ComMode ..
make