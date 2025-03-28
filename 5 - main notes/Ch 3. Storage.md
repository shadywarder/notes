**2025-03-25 15:14**
**Tags:** [course](../2%20-%20tags/course.md) [devops](../2%20-%20tags/devops.md)

## Ch 3. Storage

### Statefulness

Many docker containers are "stateless", or at least stateless in the persistent state. That is, whey you create a new container from the same image, it won't store any information from before. When you spin up a new container by running `docker run docker/getting-started`, for example, you're starting from scratch.

> [!NOTE]
> Technically speaking, any data that you store on a container *will* persist you stop that container and start it again. However, it's almost never a good idea to rely on that because that data will be lost if you spin up a new one.

That said, Docker does have ways to support a "persistent state", and the recommended way is through storage volumes.

#### Volumes Are Independent of Containers

In a future exercise, we're going to install the Ghost blogging software on your machine through Docker. As you can imagine, it would be *fairly* useless to have blogging software that doesn't save your blog posts, so we'll need to user volumes. For now, just create a new volume.

```bash
docker volume create ghost-vol
```

Make sure it worked: 

![](../attachments/Pasted%20image%2020250325152233.png)

### Ghose CMS

Cool, we've got a named volume ready to go. Now we need to install Ghost, here's a link to its image on Dockerhub.

#### Download the Image

```bash
docker pull ghost
```

#### Start the Container 

```bash
docker run -d -e NODE_ENV=development -e url=http://localhost:3001 -p 3001:2368 -v ghost-vol:/var/lib/ghost/content ghost
```

- `-e NODE_ENV=development` sets as environment variable within the container. This tells Ghost to run in "development" mode (rather than "production", for instance)

- `-e url=http://localhost:3001` sets another environment variable, this one tells Ghost that we want to be able to access Ghost via a URL on our host machine.

- We've used `-p` before. `-p 3001:2368` does some port-forwarding between the container and our host machine. 

- `ghost-vol:/var/lib/ghost/content` mounts the `ghost-vol` volume that we create before to the `/var/lib/ghost/content` path in the container. Ghost will use the `/var/lib/ghost/content` directory to persist stateful data (files) between runs.

### Creating a Website

Navigate to Ghost's admin panel: `http://localhost:3001/ghost/#/setup` and create a new website, then publish your first post.

If you navigate back to the homepage of the website, you should see you new post: `http://localhost:3011`

### Deleting the Volume

Now that we're done playing with Ghost, let's save the space on our host machine by deleting the volume.

1. Use `docker ps -a` to see *all* containers, even those that aren't running.

2. Stop the running Ghost container.

3. Remove the ghost container. Use `docker --help` to find the right command.

4. Remove the `ghost-vol` volume. Use `docker volume --help` to find the right command.

Now that it's gone, let's see what happens if we try to start the Ghost container back up and attach it to a volume that doesn't exist.

```bash
docker run -d -e NODE_ENV=development -e url=http://localhost:3001 -p 3001:2368 -v ghost-vol:/var/lib/ghost/content ghost
```

Navigate to `http://localhost:3001/` in your browser, and you should see a fresh CMS. That's weird, why no errors?

Run:

```bash
docker volume ls
```

The `ghost-vol` is back from the dead!?! It turns out the `-v ghost-vol:/var/lib/ghost/content` flag binds to a "ghost-vol" volume if it exists, otherwise, it creates it automatically!

We, we now have a fresh installation. Our post that was on the old volume is gone, but this new volume will persist if we don't delete it.

### Clean up All of Your Resources

Before we move on, let's clean up all the resources we've been playing with. 

Use `docker ps -a` to find all your containers and remove them.

Use `docker volume ls` to find all of your volumes and remove them.

## References
[Ch 3. Storage](https://www.boot.dev/lessons/e2bf006e-e99d-40ad-b9bc-83960e604a10)