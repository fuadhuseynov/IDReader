#!/bin/bash

echo ""
echo ""
echo "     3M Swipe Reader SDK - Linux Installation"
echo "    ===========================================";
echo ""
echo ""
installerDir="$( cd "$( dirname "$0" )" && pwd )"

# Reading script args
lInstallDrivers=1
lInstallLibraries=1
for lArg in $@; do

	if [[ "$lArg" == "-L" || "$lArg" == "-l" || "$lArg" == "--no-libraries" ]]; then
		echo "* Not installing libraries"
		echo ""
		lInstallLibraries=0
	else
		echo "Arg was $lArg"
	fi
done

# Prompt to read and accept software licence
echo "Press any key to read the software licence:"
read -n 1 -s
less licence.txt
echo ""
echo ""
lContinuePrompt=1
while [ $lContinuePrompt -eq 1 ]; do
	read -n 1 -p "Do you accept these terms and conditions? (Y/N): " lResponse

	if [[ $lResponse == "N" || $lResponse == "n" ]]; then
		echo ""
		echo ""
		echo "Installation cancelled"
		exit 1
	elif [[ $lResponse == "Y" || $lResponse == "y" ]]; then
		echo ""
		echo ""
		lContinuePrompt=0
	fi
done

echo "** Starting installation **"
echo ""
echo ""



if [ $lInstallLibraries -eq 1 ]; then
	echo "* Installing libraries. *"
	echo ""

	lContinuePrompt=1
	while [ $lContinuePrompt -eq 1 ]; do

		echo "All SDK libraries will be installed to /usr/lib/MMM."
		read -n 1 -p "Install libraries? (Y/N): " lResponse

		if [[ $lResponse == "N" || $lResponse == "n" ]]; then
			echo ""
			echo ""
			echo "* Skipping library installation. *"
			echo ""
			echo ""
			lContinuePrompt=0
		elif [[ $lResponse == "Y" || $lResponse == "y" ]]; then
			echo "Removing any previously installed SDK"
			sudo rm -rf /usr/lib/MMM
			sudo mkdir -m 777 /usr/lib/MMM
			echo " * Done"
			echo ""
			echo ""

			echo "Deleting any existing SDK symlinks from /usr/lib"
			sudo rm -f /usr/lib/libMMMLinuxWrapper.so
sudo rm -f /usr/lib/libMMMReaderLowLevelAPI.so
sudo rm -f /usr/lib/libMMMReaderLowLevelJava.so
sudo rm -f /usr/lib/libMMMReaderHighLevelAPI.so
sudo rm -f /usr/lib/libMMMReaderJava.so
			echo " * Done"
			echo ""
			echo ""

			echo "Copying files to /usr/lib/MMM"
			echo " * Copying libMMMLinuxWrapper.so"
cp -f ./Dist/libMMMLinuxWrapper.so /usr/lib/MMM/
echo " * Copying libCommDataDll.so"
cp -f ./Dist/libCommDataDll.so /usr/lib/MMM/
echo " * Copying libDeviceDll.so"
cp -f ./Dist/libDeviceDll.so /usr/lib/MMM/
echo " * Copying libErrorHandlerDll.so"
cp -f ./Dist/libErrorHandlerDll.so /usr/lib/MMM/
echo " * Copying libParserDll.so"
cp -f ./Dist/libParserDll.so /usr/lib/MMM/
echo " * Copying libSettingsDll.so"
cp -f ./Dist/libSettingsDll.so /usr/lib/MMM/
echo " * Copying libSwipeProtocolsDll.so"
cp -f ./Dist/libSwipeProtocolsDll.so /usr/lib/MMM/
echo " * Copying libMMMReaderLowLevelAPI.so"
cp -f ./Dist/libMMMReaderLowLevelAPI.so /usr/lib/MMM/
echo " * Copying libMMMReaderLowLevelJava.so"
cp -f ./Dist/libMMMReaderLowLevelJava.so /usr/lib/MMM/
echo " * Copying libCore_ImageProcess.so"
cp -f ./Dist/libCore_ImageProcess.so /usr/lib/MMM/
			echo ""
			echo ""

			echo "Creating symlinks for key libraries from /usr/lib/MMM to /usr/lib"
			echo " * Creating symlink for libMMMLinuxWrapper.so"
sudo ln -s /usr/lib/MMM/libMMMLinuxWrapper.so /usr/lib/libMMMLinuxWrapper.so
echo " * Creating symlink for libMMMReaderLowLevelAPI.so"
sudo ln -s /usr/lib/MMM/libMMMReaderLowLevelAPI.so /usr/lib/libMMMReaderLowLevelAPI.so
echo " * Creating symlink for libMMMReaderLowLevelJava.so"
sudo ln -s /usr/lib/MMM/libMMMReaderLowLevelJava.so /usr/lib/libMMMReaderLowLevelJava.so
			echo ""
			echo ""
			echo "* Library installation complete. *"
			echo ""
			echo ""
			lContinuePrompt=0
		fi
	done
fi

echo "** Installation complete **"
echo ""
echo ""
