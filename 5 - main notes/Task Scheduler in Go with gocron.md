**2025-02-17 15:26**
**Tags:** [go](../3%20-%20indexes/go.md)

## Task Scheduler in Go with gocron
### Why do we need to schedule tasks?
- Periodic Data Backups
- Sending Notifications or Emails
- Cleaning Up Logs and Temporary Files
- Data Synchronization
- Generating Reports
- Monitoring and Alerts
- Running Routine Maintenance

### Example of Duration Job

```go
package main

import (
	"log"
	"os"
	"os/signal"
	"syscall"
	"time"

	"github.com/go-co-op/gocron/v2"
	"github.com/google/uuid"
)

func main() {
	// create a scheduler
	s, err := gocron.NewScheduler()
	if err != nil {
		panic(err)
	}

	// duration job
	j, err := s.NewJob(
		gocron.DurationJob(
			5*time.Second,
		),
		gocron.NewTask(
			func(a string) {
				log.Println(a)
			},
			"every 5 seconds",
		),
		gocron.WithName("duratinjob: every 5 seconds"),
		gocron.WithEventListeners(
			gocron.BeforeJobRuns(
				func(jobID uuid.UUID, jobName string) {
					log.Printf("job starting: %v %v\n", jobID, jobName)
				},
			),
			gocron.AfterJobRuns(
				func(jobID uuid.UUID, jobName string) {
					log.Printf("job completed: %v %v\n", jobID, jobName)
				},
			),
			gocron.AfterJobRunsWithError(
				func(jobID uuid.UUID, jobName string, err error) {
					log.Printf("job had an error: %v %v %v\n", jobID, jobName, err.Error())
				}),
		),
	)
	if err != nil {
		panic(err)
	}

	// cron job
	s.NewJob(
		gocron.CronJob(
			"*/10 * * * *",
			false,
		),
		gocron.NewTask(
			func(a string) {
				log.Println(a)
			},
			"cronjob: every 10 mins.",
		),
		gocron.WithName("cronjob: every 10 mins."),
	)

	// daily job
	s.NewJob(
		gocron.DailyJob(
			1,
			gocron.NewAtTimes(
				gocron.NewAtTime(23, 10, 00),
				gocron.NewAtTime(05, 30, 00),
			),
		),
		gocron.NewTask(
			func(a string, b string) {
				log.Println(a, b)
			},
			"dailyjob",
			"runs daily",
		),
		gocron.WithName("daily job: 2 times everyday"),
	)

	// one time job
	s.NewJob(
		gocron.OneTimeJob(
			gocron.OneTimeJobStartDateTime(time.Now().Add(10*time.Second)),
		),
		gocron.NewTask(
			func(a string) {
				log.Println(a)
			},
			"onetimejob",
		),
	)

	// random duration job
	s.NewJob(
		gocron.DurationRandomJob(2*time.Minute, 4*time.Minute),
		gocron.NewTask(
			func(a string) {
				log.Println(a)
			},
			"randomdurationjob",
		),
	)

	log.Println(j.ID())

	s.Start()

	stop := make(chan os.Signal, 1)
	signal.Notify(stop, syscall.SIGINT, syscall.SIGTERM)

	go func() {
		<-stop
		log.Println("interrupt signal received. exiting...")
		if err := s.Shutdown(); err != nil {
			panic(err)
		}
		os.Exit(0)
	}()

	for {
	}
}
```

### Goroutines vs gocron
- Goroutines lack built-in scheduling capabilities.
- gocron abstracts the complexity of managing schedules offering a clear, declarative syntax for defining task schedules
- Avoid running long-running processes directly in Goroutines or gocron.

## References
[Task Scheduler in Go with gocron - Part 1](https://www.youtube.com/watch?v=WNALGb5YZ6A)
[Task Scheduler in Go with gocron - Part 2](https://www.youtube.com/watch?v=UfmzataUVYc)