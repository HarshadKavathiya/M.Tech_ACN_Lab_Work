set ns [new Simulator]
$ns color 1 blue
$ns color 2 red
$ns color 3 yellow

#NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#open trace file

set f [open tcp.tr w]
$ns trace-all $f

#define a "finish" procedure

proc finish {} 	{
		global ns nf f
		$ns flush-trace
		close $nf
		close $f
		exec nam out.nam &
		exit 0
	} 


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 1Mb 50ms DropTail
$ns duplex-link $n1 $n2 10Kb 5ms DropTail
$ns duplex-link $n0 $n2 100Kb 10ms DropTail

$ns queue-limit $n0 $n1 10
$ns queue-limit $n1 $n2 10
$ns queue-limit $n0 $n2 10

#$ns duplex-link-op $n0 $n1 orient right
#$ns duplex-link-op $n1 $n2 orient right


$ns duplex-link-op $n1 $n2 queuePos 0.5
$ns duplex-link-op $n0 $n2 queuePos 0.5
$ns duplex-link-op $n2 $n1 queuePos 0.5

set tcp [new Agent/TCP]

$tcp set class_ 1
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink


set tcp1 [new Agent/TCP]

$tcp1 set class_ 2
$ns attach-agent $n2 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp1 $sink1

set tcp2 [new Agent/TCP]

$tcp2 set class_ 3
$ns attach-agent $n1 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n0 $sink2
$ns connect $tcp2 $sink2








set ftp [new Application/FTP]
$ftp attach-agent $tcp

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2

$ns at 0.5 "$ftp start"
$ns at 1.5 "$ftp1 start"
$ns at 1.5 "$ftp2 start"
$ns at 50.5 "$ftp2 stop"
$ns at 60.5 "$ftp stop"
$ns at 70.5 "$ftp1 stop"
$ns at 71.0 "finish"
$ns run
