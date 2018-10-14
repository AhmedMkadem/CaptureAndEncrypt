## Overview
The goal of this project is to design and implement a cryptographic protocol ensuring a secure storage of sensitive data during a mission of
autonomous system and a mechanism capable of protecting the collected data in case of interception of the system.
Sensitive data are collected using a cam and then encrypted using the AES encryption algorithm with respect to the Forward Secrecy cryptographic feature.

## Usage
After cloning the repository, compile the program:

`make exec`

Run the executable:

`./exec`

This will start taking 10 snapshots from the webcam and encrypt them.

To decrypt the snapshots, compile the decryption program:

`make decryption`

And run it:
`./decrypt`

## Author
This project has been completed during a Semester Project in Fall 2016 at Eurecom by me, it was supervised by [Aurélien Francillon](http://s3.eurecom.fr/~aurel/).
