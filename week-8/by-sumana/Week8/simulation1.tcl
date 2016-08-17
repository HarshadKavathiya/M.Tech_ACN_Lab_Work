set ns [ new Simulator]
$ns color 1 blue

set nf [ open out.nam w]
$ns namtrace-all $nf

set f [ open tcp.tr w]
$ns trace-all $f

proc finish {} {
		global ns nf f
		$ns flush-trace
		close $nf
		close $f
		exec nam out.nam
		exit 0
	}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]


$ns duplex-link $n0 $n1 1Mb 50ms  DropTail
$ns duplex-link $n1 $n2 100kb 5ms  DropTail

$ns queue-limit $n1 $n2 10

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

$ns duplex-link-op $n1 $n2 queuePos 0.5

#Setup TCP
set tcp [new Agent/TCP]
$tcp set class_ 1
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink

#Setup a FTP over TCP connection
set ftp [ new Application/FTP]
$ftp attach-agent $tcp


$ns at 0.5 "$ftp start"
$ns at 50.5 "$ftp stop"
$ns at 51.0 "finish"

$ns run



