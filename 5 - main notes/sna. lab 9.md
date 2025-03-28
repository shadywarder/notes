**Author: Sergey Razmakhov**
**Group: CBS-02**
**Lab 9: Docker compose, volumes, and cache**

### 1. Secret Management

The can use environment variables (`.env` file) to manager secretes for a containerized FastAPI application running in a production environment. 

However, `.env` files pose some risks:

- They may be accidentally committed to version control system.

- File system access on a hacked host could expose them.

If there are no other options, we are obliged to exclude `.env` via `.dockerignore` and `.gitignore`.

There are also dedicated secrets management tools such as Azure Key Vault, AWS Secrets Manager, or GCP Secret Manager, that securely store secrets.

### 2. Three Instances

In order to add one more instance to the our application we need to adjust `docker-compose.yaml` and nginx's `default.conf` file.

I add one more service in the `docker-compose.yaml` file: 

```yaml
web3:
    build: ./app
    volumes:
      - ./app:/app
    environment:
      DATABASE_URL: ${DATABASE_URL}
      SERVER_ID: Sergey
    depends_on:
      - db
```

Surely, we need to update `nginx` service's `depends_on` option.

```yaml
nginx:
    image: nginx:latest
    ports:
      - "8080:80"
    volumes:
      - ./nginx:/etc/nginx/conf.d
    depends_on:
      - web1
      - web2
      - web3
```

Here is the updated nginx config: 

```conf
upstream webapp {
  server web1:8000;
  server web2:8000;
  server web3:8000;
}

server {
  listen 80;

  location / {
      proxy_pass http://webapp;
  }
}
```

Running  containers:

![](../attachments/Pasted%20image%2020250324202440.png)

Proof that the load balancer is forwarding requests to all three instances:

![](../attachments/Pasted%20image%2020250324201756.png)

![](../attachments/Pasted%20image%2020250324201804.png)

![](../attachments/Pasted%20image%2020250324201816.png)

### 3. Database Backup

To restore the database from backups I copied the backup from the backup container and execute its content into "corrupted" container. 

![](../attachments/Pasted%20image%2020250324214034.png)

All other details in the files.

### 4. Container Orchestration

Orchestration systems automate deployment, scaling, and lifecycle management, ensuring applications' security and efficiency.

**Key Features of Container Orchestration Systems**

1. Automated Deployment and Rollbacks;

2. Dynamic Scaling;

3. Self-Healing;

4. Secret and Configuration Management;

5. Monitoring and Logging.