#!/bin/bash
desiredvalue=$1

if [ "$desiredvalue" == "" ] ; then
	desiredvalue=0
fi

echo "desiredvalue=$desiredvalue"

echo "=====* ORIG *====="

cpucnt=`grep Core /proc/cpuinfo | wc -l`

address="0x1A4"

cpuid=0
while [ $cpuid -lt $cpucnt ];do
	echo "Core $cpuid"
	echo rdmsr -x -p "$cpuid" $address
	rdmsr -x -p "$cpuid" $address
	cpuid=$(( $cpuid + 1 ))
done

echo "=====* MODIFY *====="

cpuid=0
while [ $cpuid -lt $cpucnt ];do
	echo "Core $cpuid"
	echo wrmsr -p "$cpuid" $address $desiredvalue
	wrmsr -p "$cpuid" $address $desiredvalue
	cpuid=$(( $cpuid + 1 ))
done




