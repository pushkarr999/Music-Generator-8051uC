## Programming your radio
This guide will help you to provide wireless communication functionality to the robot. We use  _OpenMesh OM5P-AN_ or _OM5P-AC_ Radio for this purpose.

  <img src="https://docs.wpilib.org/en/stable/_images/openmesh-radio-status-lights.png" alt="Radio"/>
</p>

Before programming your radio :
* Disable all other network adapters except ethernet adapter.
* Power the radio using 12V/2A output on the VRM. Alternatively, you can also use suitable DC adapter.

## Prerequisites
* Make sure you have installed `FRC Radio Configuration Utility` on your machine with administrative privileges.
* The Java Runtime is required to use the FRC Bridge Configuration Tool. Many computers will already have Java installed, you can check by looking for a Java icon in the Control Panel. If you do not have Java already installed, download and install it from [http://www.java.com/en/download/index.jsp](http://www.java.com/en/download/index.jsp)
## Using the software
* Connect the radio using ethernet cable to you PC and the ethernet port of the radio which is closest to the power jack. Turn on the radio by connecting the power jack to VRM or a suitable adaptor.
* Launch the program as administrator from the start menu or desktop stortcut.
> If you need to locate the program, it is installed to `C:\Program Files (x86)\FRC Radio Configuration Utility`. For 32-bit machines the path is `C:\Program Files\FRC Radio Configuration Utility`.

<p align="center">
  <img src="https://docs.wpilib.org/en/stable/_images/radio-launch.png" alt="launch the program"/>
</p>

* Allow the program to make changes if prompted.
* Select the network interface, typlically for windows system you have to select "Local Area Network" or "Ethernet" from the drop-down. Click refresh if you don't see an interface.
<p align="center">
  <img src="https://docs.wpilib.org/en/stable/_images/select-network-connection.png" alt="network_interface"/>
</p>

* Unplug the power from the radio and press the "Load Firmware" button. Plug the power when prompted.
* Make sure OpenMesh radio is selected from the radio dropdown.
<p align="center">
  <img src="https://docs.wpilib.org/en/stable/_images/openmesh-firmware.png" alt="settings"/>
</p>

* Enter the Team Number and Robot Name. WPA Key will work as the password for the radio network.
> The network SSID has the format "TeamNumber_RobotName".
> Example - For team number "1402" and robot name "bot", SSID will be "1402_bot"

* Click on Configure. This will start the configurayion of the network.
<p align="center">
  <img src="https://docs.wpilib.org/en/stable/_images/config-in-progress.png" alt="inprogress"/>
</p>

* Once the configuration is complete click on "OK" and check for the network in the available networks.
<p align="center">
  <img src="https://docs.wpilib.org/en/stable/_images/config-completed.png" alt="success"/>
</p>

## Troubleshooting tips
- If `Bridge Programming fail` error occurs. Try :

<p align="center">
  <img src="https://docs.wpilib.org/en/stable/_images/config-errors.png" alt="program fail bridge"/>
</p>

	1. Load the firmware again.
	2. Check if other network adaptors are disabled.
	3. Disable the firewall temporarily.
	4. Restart your PC.

* Plug the ethernet cable directly into the radio with no devices in between.
*  Disable all other adapters (except ethernet) using https://www.windowscentral.com/how-enable-or-disable-wi-fi-and-ethernet-network-adapters-windows-10.
* If the configuration fails with the error `Failed to change IP Address`, see https://docs.wpilib.org/en/stable/docs/yearly-overview/known-issues.html#failed-to-change-ip-address-in-radio-configuration.
