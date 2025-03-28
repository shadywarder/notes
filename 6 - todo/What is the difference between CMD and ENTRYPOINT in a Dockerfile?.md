**2025-03-17 20:14**
**Tags:** [devops](../2%20-%20tags/devops.md)

## What is the difference between CMD and ENTRYPOINT in a Dockerfile?

In Dockerfiles there are two commands that look similar to me: `CMD` and `ENTRYPOINT`. But I guess that there is a (subtle?) difference between them - otherwise it would not make any sense to have two commands for the very same thing.

The documentation states for `CMD`

>The main purpose of a CMD is to provide defaults for an executing container.

and for `ENTRYPOINT`:

>An ENTRYPOINT helps you to configure a container that you can run as an executable.

So, what's the difference between those two commands?

---

Docker has a default entrypoint which is `/bin/sh -c` but does not have a default command. 

When you run docker like this: `docker run -i -t ubuntu bash` the entrypoint is the default `/bin/sh -c`, the image is `ubuntu` and the command is `bash`.

The command is run via the entrypoint. i.e., the actual thing that gets executed is `/bin/sh -c bash`. This allowed Docker to implement `RUN` quickly by relying on the shell's parser.







## References
[]