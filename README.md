# fPipe

fPipe is a reverse engineered recreation of fpipe.exe by Robin Keir 

fPipe is a very small tcp/udp port redirector for Windows that uses the winsock library

The source code is the product of reverse engineering the psuedocode output from IDA

Check out my talk at Kernelcon 2022 to learn more

# Compilation Tips

tcc can be used to compile the project, you will need to import various libraries

```
tcc.exe -impdef ws2_32.dll
tcc.exe fpipe.c ws2_32.def 
```

Visual Studio can be used to compile this as well

# Shrinking the file size

http://ku.nz/blog/shrinkingc.html

Use visual studio 2008 linking against msvcrt.dll

Use UPX to compress the binary
