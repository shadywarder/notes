**Author: Sergey Razmakhov**
**Group: CBS-02**
**Lab 5: Processes and signals**

##### 1. What are zombie processes? How can you find and kill them?
A zombie process is a place-holder for a process which has terminated, but which has not yet been "acknowledged" by its parent.

We can locate them with following pipeline: 

```bash
ps -A -ostat,ppid | awk '/[zZ]/{ print $2 }'
```

In order to kill them, we may kill their parents =)

```bash
kill $(ps -A -ostat,ppid | awk '/[zZ]/ && !a[$2]++ {print$2}')
```

##### 2. What are the differences between `kill`, `killall`, and `pkill`?
- `kill` will send a signal to the OS for a given process id, by default this is SIGTERM. 
- `killall` will send a signal to all processes matching a certain name exactly, by default this is SIGTERM.
- `pkill` will send a signal to all processes that match a given pattern. It uses `pgrep` under the hood.

##### 3. `top` command

Here is the the data in the `Tasks` and `%Cpu(s)` lines.

![](../attachments/Pasted%20image%2020250224164107.png)

**Tasks**
- `total` - number of process of any state.
- `running` - number of process that are handling requests, executing normally, and have CPU access.
- `sleeping` - number of process that are awaiting resources.
- `stopped` - number of exiting and releasing resources processes.
- `zombie` - number of processes that are waiting for its parent process to release it.

**%Cpu(s)**
- `us` - % of time spent running user processes.
- `sy` - % of time spent running the kernel.
- `ni` - % of time spend running with manually configured nice values.
- `id` - % of time idle (if high, CPU may be overworked).
- `wa` - % of wait time (if high, CPU is waiting for I/O access).
- `hi` - % of time managing hardware interrupts.
- `si` - % of time managing software interrupt.
- `st` - % of virtual CPU time waiting for access to physical CPU.

##### 4. Infinity sleeping

![](../attachments/Pasted%20image%2020250224185957.png)

```bash
#!/bin/bash

pids=$(ps a | awk '/fun[0-9]+process/ {print $1}')

if [[ -n $pids ]]
then 
	for pid in $pids; do
		echo "found process with pid: $pid"
		if kill $pid; then
			echo "process(es) killed."
		else 
			echo "failed to kill process with pid: $pid"
		fi
	done
else 
	echo 'no matching processes found.'
fi
```

#### 5. Hello world!

![](../attachments/Pasted%20image%2020250224192922.png)

```bash
#!/bin/bash

trap 'echo "Interrupt received"' SIGUSR1

while [ 1 ]; do
	echo "Hello world!"
	sleep 10
done
```

##### 6. Monitor

![](../attachments/Pasted%20image%2020250224202818.png)

```bash
#!/bin/bash

log_file="/var/log/system_utilization.log"

sudo touch "$log_file" 2>/dev/null
sudo chmod 644 "$log_file"

while [[ 1 ]]; do
	timestamp=$(date)	
	cpu=$(top -b -n 1 | awk '/^%Cpu/ {print 100-$8}')
	mem_total=$(free -m | awk '/Mem:/ {print $2}')
	mem_used=$(free -m | awk '/Mem:/ {print $3}')
	mem_percent=$(echo "scale=2; $mem_used / $mem_total * 100" | bc)
	disk_percent=$(df --output=pcent / | tail -n1 | tr -d ' %')

	echo Timestamp: $timestamp | sudo tee -a "$log_file" >/dev/null
	echo CPU usage: $cpu% | sudo tee -a "$log_file" >/dev/null
	echo Memory usage $mem_percent% | sudo tee -a "$log_file" >/dev/null
	echo Disk usage $disk_percent% | sudo tee -a "$log_file" >/dev/null
	echo "" | sudo tee -a "$log_file" >/dev/null

	sleep 15
done
```