Lab 2.1 - ClockWall
===================

To compile
---------------------------------------
```
go build clock2.go
go build clockWall.go
```

To run
---------------------------------------
Open the ports with ./clock2:

```
TZ=US/Eastern ./clock2 -port 8010
TZ=Asia/Tokyo ./clock2 -port 8020 
TZ=Europe/London ./clock2 -port 8030
```

Then by using ./clockWall, pass the parameters
```
./clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030
```