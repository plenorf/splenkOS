# splenkOS

## Features
Limine Bootloader
Commands
Memory Manager
Resolution detection
PS/2 support for keyboards
GDT
Logging
Scheduler


## Compiling
To compile the OS, type "`make`", and then you can either choose to create an ISO or hard disk image. The scripts are already there for easy access.  
To create an ISO, run: `./iso.sh`  
To create a disk image, run: `./hdd.sh`  
  
And then run the OS with `./run.sh`  

Alternatively, there is an experimental Dockerfile for building in a controlled environment. Run:

```bash
docker build -t splenkos .
```

It is still in progress, but can show you build errors.

## Commands
There are a total 6 commands and these are
`help`: Displays commands. Usage `time`
`time`: Displays time since boot. Usage `time`
`sleep`: sleeps the system for a set amount of time in ms. Usage `sleep 100` 
`echo`: echos text. Usage: `echo Hello World`
`splenkfetch`: displays system info with ascii art of splenk. Usage `splenkfetch`
`halt`; stops the system from running. Usage: `halt`
