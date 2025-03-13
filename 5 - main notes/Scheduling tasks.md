**2025-03-03 22:45**
**Tags:** [os](../2%20-%20tags/os.md)

## Scheduling tasks
### Create cron jobs
Let's create an example script `job.sh`. We can check `log.txt` at any time to see whether our scheduled job has run. 

```bash
#!/bin/bash
echo `date +"%T-%M-%d %T"`" - Hello world" >> /home/username/log.txt
```

#### Adding the job to the user crontab
To understand the user crontab, let's add the script to it manually

```bash
crontab -e
```

This command will open an editor to edit the existing user crontab. Let's append our cron expression:

```bash
30 0 * * * /home/username/job.sh
```

This schedules the script to run every day, 30 minutes after midnight.

We also need to be sure that the current user has execute permissions for this script. So, let's use the `chmod` command to add them:

```bash
chmod u+x /home/username/job.sh
```

Now, `job.sh` is scheduled and will run every day. We can test this by inspecting the `log.txt` file.

#### Adding the job to the system crontab
To understand the system crontab, let's also add this script to it manually.

The system crontab file is kept in `/etc/crontab`. Let's append the following line:

```bash
30 0 * * * root /home/username/job.sh
```

We should note that we need to specify the root username. This is because jobs in system cron are system jobs and will be run by the root user.


#### Script for adding the job to the user crontab
Now let's try automating the process to add to the user crontab. Install a new file to crontab.

Let's first create a new script file:

```bash
touch /home/username/myScript.sh
```

The first thing our script will do is take a copy of all current jobs. Do not forget to add executable right for the script to work.

```bash
#!/bin/bash
crontab -l > crontab_new
```

We now have all the previous jobs in the `crontab_new` file. This means we can append our new job to it and then rewrite the crontab by using the edited file as an input argument to the crontab command:

```bash
echo "30 0 * * * /home/username/job.sh" >> crontab_new
crontab crontab_new
```

Since the `crontab_new` file is temporary, we can remove it:

```bash
remove crontab_new
```

This method works well, though it does require the use of a temporary file. The main idea here is to add multiple tasks to the existing user jobs. Let's see if we can optimize it further.
## References