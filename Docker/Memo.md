# Section 1: Course Introduction and Docker Intro

1. Getting Requirements
2. Docker Install
3. Container Basics
4. Image Basics
5. Docker Networking
6. Docker Volumes
7. Docker Compose
8. Orchestration
9. Docker Swarm
10. Kubermetes 
11. Swarm vs. K8s
12. Q&A
13. File Reviews
14. References Galore

# Section 2: The Best Way to Setup Docker for your OS   
> docker version 
(觀看 docker 版本)

> docker ps  
(查看目前執行的 containers)

> https://hub.docker.com/

> Windows 10 Pro/Enterprise -> Docker Desktop for Windows 


# Section 3: Creating and Using Containers Like a Boss

## 18. Check Our Docker Install and Config 

> docker info 

## 19. Starting a Nginx Web Server 

## 21. Container VS. VM: It's Just a Process

## 27. Docker Networks: Concepts for Private and Public Comms in Containers

## 29. Docker Networks: CLI Management of Virtual Networks
> docker network ls 
(show networks)

> docker network inspect <NETWORK_NAME>
(ex: 'docker network inspect bridge') (inspect a network)

> docker 的 network 種類
(--network bridge, Default Docker virtual network, which is NAT'ed behind the Host IP)
(--network host, It gains performance by skipping virtual networks but sacrifices security 
 of container model)
(--network none, removes eth0 and only leaves you with localhost interface in container)

> docker network create <NETWORK_NAME> 
('docker network create my_app_net')
(建立 network)
 
> docker container run -d --name new_nginx --network my_app_net nginx
(container 執行的時候指定使用network)

> docker network connect 
(ex: 'docker network connect my_app_net webhost')
(attach a network to container)

> docker network disconnect 
(ex: 'docker network disconnect my_app_net webhost')
(detach a network from container)

> docker container inspect <CONTAINER>
(docker container inspect <container>, can see the network status)

> docker container disconnect 


## 30. Docker Networks: DNS and How Containers Find Each Other 
> docker container run -d --name my_nginx --network my_app_net nginx
> docker container run -d --name new_nginx --network my_app_net nginx
(建立兩個 containers, 連到 my_app_net 這個 network)

> docker container exec -it new_nginx ping my_nginx
(在container 中 執行 ping command)
(不能pin, 先執行 > docker container exec -it my_nginx bash 
 再執行 > apt-get update 
 再執行 > apt-get install -y iputils-ping
 才能使用 ping)

 > docker network ls
 (列出所有 networks)

>  docker container create --help
(可以看到 --link 可以指定 network)

## 32. Assignment Answers: Using Containers for CLI Testing 

> docker container run --rm -it centos:7 bash 
(安裝 centos, --rm: automatically remove the container when it exits)

> yum update curl 

> docker container run --rm -it ubuntu:14.04 bash 
(安裝 ubuntu)

> apt-get update && apt-get install -y curl

> curl google.com 
(return html)

## 33. Assignment: DNS Round Robin Test 

1. Create a new virtual net work(default bridge driver)

2. Create two containers from elasticsearch:2 image

3. use '-network-alias search' when creating network 
  to give them an additional DNS name to respond to 
 
4. Run alpine nslookup search with --net 
  to see the two containers list for the same DNS name

5. Run centos curl -s search:9200 with --net 
  to see both 'name' fields show 

## 34. Assignment Answers: DNS Round Robin Test 

> docker network create dude 
(create a network)

> docker container run -d --net dude --net-alias search elasticsearch:2
(create container and link to dude network and use alias)

> docker container run --rm --net dude alpine nslookup search 
(create another container to run 'nslookup search' command)

> docker container run --rm --net dude centos curl -s search:9200
(create another container to run 'curl -s search:9200' command)
(多跑幾次 結果中的 "name" 會變化)

> docker container rm -f 640 5d6
(強制刪除container)

# Section 4: Container Images, Where to Find Them and How To Build Them

seection 4

## 35. What's In An Image(and What Isn't)

## 36. The Mighty Hub: Using Docker Hub Registry Images

> docker image ls 
(列出有的images)

> docker pull <image name>; ex: docker pull nginx
(下載image, 最新版本的)

> docker pull nginx:1.17.8 
(用tag指定下載哪個版本的image)

> 如果下載相同image ID, 但是不同tag
其實只有存一份, 但是在 "docker image ls" 指令下 會有多行
不同 tag 會列在不同行

## 37. Image and Their Layers: Discover The Image Cache

> reference: https://docs.docker.com/storage/storagedriver/

> docker history <image name>; ex: docker history nginx
(觀看image的 history/layer, 舊用法)

> docker image history <image name>
(同上)

> docker image inspect <image name>; docker image inspect nginx 
(returns JSON metadata about the image)

## 38. Image Tagging and Pushing to Docker Hub

> docker image tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]
(Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE)

> <user>/<repo>:<tag> 
(如果沒指定的話 default tag 是 'latest')
(official image 的話 不需user, 是在 root)

> docker pull mysql/mysql-server
(下載其他使用者版本的 mysql)

> docker image tag nginx seishin/nginx
(retag existing docker image, 執行 'docker image ls' 會多一行)

> docker image push NAME[:TAG]
(uploads changed layers to a image regitry)

> user name 真的一定要相同才可以push

> docker login [SERVER]
(要 login 才可以 push)
(然後記得再登出 'docker logout')


## 39. Building Images: The Dockerfile Basics

> reference: https://docs.docker.com/engine/reference/builder/

> docker file: recipe to create your images

> GOTO: \Github\udemy-docker-mastery\dockerfile-sample-1\Dockerfile

> docker build -f some-dockerfileName
(用 -f 指定Dockerfile檔案名稱, 預設是 Path/Dockerfile)

> FROM COMMAND
> FROM debian:stretch-slim
(此 image 要把哪個image當作base來建立)
(all images must have a 'FROM', 一定要有)
(usually from a minimal Linux distribution like debian or (even better) alpine)
(if you truly want to start with an empty container, use FROM scratch)

> Package Manager 
(PM's like apt and yum are one of the reasons to build containers FROM 
Debian, Ubuntu, Fedora or CentOS)

> ENV COMMAND
> ENV NGINX_VERSION 1.13.6-1~stretch
  ENV NJS_VERSION   1.13.6.0.1.14-1~stretch
(設定環境變數, dockerfile下面可以用, 且 container在執行的時候換設定成 envvar也可以用)
(key/value, work evenywhere, on every OS and config)


> RUN COMMAND
(optional commands to run at shell inside container at build time)
(this one adds package repo for nginx from nginx.org and installs it)
(docker file 內部是照順序執行下來的, 每一步驟都是layer
所以前後順序放不一樣會有差)

> log 的內容在 docker file 處理
在container裡面的log 不要存到log file裡面, 只要確保有輸出到 stdout, stderr
其他的由docker log collector 處理
避免存在container裡面, 會造成access log 的麻煩

> EXPOSE COMMAND
(expose these ports on the docker virtual network)
(you still need to use -p or -P to open/forward these ports on host)

> CMD COMMAND
(一定要有的, 當從image run起container後, 最後會執行的指令
 或是 restart stopped container後會執行的指令)
(only one CMD allowed, so if there are multiple, last one wins)

## 40. Building Images: Running Docker Builds

> GOTO: \Github\udemy-docker-mastery\dockerfile-sample-1\Dockerfile

> docker image ls 

> docker image build -t <imageName:imageTag> <PATH>
(ex: 'docker image build -t customnginx .')

> 每一個 step 會有一個 cache, 如果沒有改變的話會拿cache 所以才會快

> 盡量讓 前面步驟是較少改變, 後面步驟是較常改變, 這樣build 速度才會比較快

## 41. Building Images: Extending Official Images

> GOTO: \Github\udemy-docker-mastery\dockerfile-sample-2\Dockerfile

> 使用 FROM command 時, 最好都在image name 後面指定版本 
(ex: FROM nginx:latest)

> WORKDIR COMMAND
(用來修改工作路徑, 相當於 cd, 但是比較prefer 用 WORKDIR)
(ex: 'WORKDIR /usr/share/nginx/html')

> COPY COMMAND
(將本機的檔案 複製到 image當中)
(ex: COPY index.html index.html)

> docker container run -p 80:80 --rm nginx

> docker image build -t nginx-with-html 
(build dockerfile-sample-2 範例的 docker file)

> docker container run -p 80:80 --rm nginx-with-html
(localhost 看首頁會變為 \dockerfile-sample-2\index.html的內容)

> docker image tag nginx-with-html:latest haochinnate/nginx-with-html:latest

> docker push haochinnate/nginx-with-html:latest
(重新tag然後把新的image傳上去 docker hub)

## 42. Build Your Own Dockerfile and Run Containers From it 

> Dockerfiles are part process workflow and part art

> base on Node.js 

> GOTO: \Github\udemy-docker-mastery\dockerfile-assignment-1\Dockerfile

> docker container run -p 80:3000 --rm node-assignment
(或是不先 pull image, 直接 container run 裡面 用 haochinnate/node-assignment 也可以)

## 44. Using Prune to Keep Your Docker System Clean 

> docker image prune 
(remove dangling images)

> docker system prune 
(remove unused data)

> docker system df 
(可以觀看有多少 image/container/volumes 還有容量)


# Section 5: Container Lifetime & Persistent Data: Volumes

> References 
* An introduction to immutable infrastructure(https://www.oreilly.com/radar/an-introduction-to-immutable-infrastructure/)

* THE TWELVE-FACTOR APP(https://12factor.net/) 

  3. Config
    * NEVER hard coded setting in images or apps, which would be different for each environment(environment: local machine, dev test server, staging server, production server)
    * __strict separation of config from code__
    * Using everying abour config in _environment variables_
    * [3 Docker Compose features for improving team development workflow](https://www.oreilly.com/ideas/3-docker-compose-features-for-improving-team-development-workflow)
    * 密碼等等的事後再透過 ENV 內的路徑去取得


* 12 Fractured Apps(https://medium.com/@kelseyhightower/12-fractured-apps-1080c73d481c)

* Manage data in Docker(https://docs.docker.com/storage/)

## 45. Container Lifetime & Persistent Data

* Containers are usually immutable (一成不變的) & ephemeral (短暫的)

* "immutable infrastructure": only re-deploy containers, never change

* Two ways for "persistent data": Volumes & Bind Mounts

* Volumes: make special location outside of container UFS(Unit File System)

* Bind Mounts: link container path to host path

## 46. Persistent Data: Data Volumes

* VOLUME COMMAND in Dockerfile
(example in mysql: VOLUME /var/lib/mysql)

* docker image inspect mysql
(["Config"].["Volumes"] 可以看到設定)

* docker container inspect <containerName> 
(同上, 也可看到 Volumes的值)
(還有一個 ["Mounts"] 的參數, 裡面有 ["Source"] 和 ["Destination"])


* docker container run -d --name mysql -e MYSQL_ALLOW_EMPTY_PASSWORD=True mysql

* docker volume ls 
(列出所有 volumes)

* docke volume inspect <VOLUME>
(觀看 volume資訊, 要完整打出 VOLUME NAME)

* 移除 container 後, volume 仍會保留

* named volumes, readable name
docker container run -d --name mysql -e MYSQL_ALLOW_EMPTY_PASSWORD=True -v mysql-db:/var/lib/mysql mysql
(在執行的時候指定 volume 名稱, 或開一個volume)

* docker volume create
(Create a volume)




## 47. Persistent Data: Bind Mounting

* Maps a HOST file/directory to a CONTAINER file/directory

* Can't use in Dockerfile, must be at "container run"
(windows ex: ... run -v //c/Users/somepath:/path/container)

* docker container run -d --name nginx -p 80:80 -v ${pwd}:/usr/share/nginx/html nginx
($pwd for shell shortcut to print working directory)

* docker container exec -it nginx bash
(bash 進入container看檔案結構, 看是否真的有bind)

* 兩個路徑會指到同一位置, 新增/刪除檔案都會同步
  "Mounts": [
            {
                "Type": "bind",
                "Source": "/host_mnt/d/CodingWorkspace/Github/udemy-docker-mastery/dockerfile-sample-2",
                "Destination": "/usr/share/nginx/html",
                "Mode": "",
                "RW": true,
                "Propagation": "rprivate"
            }
        ],

## 48. Database Upgrades with Named Volumes

* Dockerfile of postgres: VOLUME /var/lib/postgresql/data

* docker container run -d --name psql -v psql:/var/lib/postgresql/data postgres:9.6.1

* docker container logs -f psql

* docker volume ls 可以看到新 volume: psql

* 先把 psql 停止, 再跑一個 psql2, 是用 9.6.2 版本跑

* 就可以讓 psql 和 psql2 使用到同一個 volume

## 50. Edit Code Running in Containers With Bind Mounts

* GOTO: \udemy-docker-mastery\bindmount-sample-1

* docker run -p 80:4000 -v ${pwd}:/site bretfisher/jekyll-serve
(跑起來即有網頁可瀏覽, 編輯 bindmount-sample-1\_posts\ 內的檔案就會連動網頁內容)
(KEYPOINT: '-v ${pwd}:/site')


# Section 6: Making It Easier with Docker Compose: The Multi-Container Tool

Reference:

* YAML get started(https://yaml.org/start.html)

* YAML reference card(https://yaml.org/refcard.html)

* Compose file versions(https://docs.docker.com/compose/compose-file/compose-versioning/)

## 52. Docker Compose and The docker-compose.yml File

Introduction:

* Docker compose: combination of command line tool and configuration files

* WHY
  1. configure relationships between containers
  2. save docker container run settings(options) in easy-to- read file
  3. create one-linear developer environment startups

* TWO parts:
  1. YAML-formatted file that describes solution options
    * containers
    * networks
    * volumes
    * environment variables, images, etc...
  2. CLI tool docker-compose used for local develop/test automation 

* Compose YAML format has own versions

* "docker-compose --help"

* 預設名稱: docker-compose.yml, 也可使用 docker-compose -f 指定名稱

* GOTO: \udemy-docker-mastery\compose-sample-1\template.yml
  有解釋名稱

## 53. Trying Out Basic Compose Commands

* docker-compose CLI: not a production-grade tool but ideal for local development and test

* "docker-compose up" # setup volumes/networks and start all containers

* "docker-compose down" # stop all containers and remove container/volume/netowrk

* 如果你的專案有 "Dockerfile" 和 "docker-compose.yml", 那當有新的開發人員來時, 就是需要做
  1. git clone github.com/some/software
  2. docker-compose up 

* GOTO: \udemy-docker-mastery\compose-sample-2

* "docker-compose up -d" # -d for detach, run containers in the background

* "docker-compose ps" same as "docker container ps"

* "docker-compose top" # Display the running processes

## 55. Build a Compose File for a Multi-Container Service

* GOTO: \PieceNote\Docker\assignment\055-compose-assignment-1

* 編輯完成後, 再下 "docker-compose up" 指令

* "docker-compose down -v", 移除container外, 也會移除 volume

## 56. Adding Image Building to Compose Files

* 前面如果image不存在, 是會下載 image

* 如果在執行 "docker-compose up"時, 在cache沒有找到image才會build

* 或是執行 "docker-compose build" 也會 rebuild

* GOTO: \udemy-docker-mastery\compose-sample-3

* docker-compose.yml 裡面 
  原本是 image:<IMAGE_NAME>
  改成 build: ...
  如果再加上 image: nginx-custom, 會把build的結果存起來tag為 nginx-custom

* "docker-compose up -d", -d for detached

* "docker-compose down --rmi local/all", 移除container外, 也會移除 images 

## 57. Compose For Run-Time Image Building and Multi-Container Development

* building custom drupal image 

* RUN apt-get update && apt-get install -y git \
      && rm -rf /var/lib/apt/lists/* 

* drupal 裡面 database 設定
  資料庫名稱: postgres, 使用者: postgres
  主機: localhost -> postgres

# Section 7: Swarm Intro and Creating a 3-Node Swarm Cluster

Reference:

* [Docker 1.12 Swarm Mode Deep Dive Part 1: Topology](https://www.youtube.com/watch?v=dooPhkXT9yI)

* [Docker 1.12 Swarm Mode Deep Dive Part 2: Orchestration](https://www.youtube.com/watch?v=_F6PSP-qhdA)

* [Heart of the SwarmKit: Topology Management](https://speakerdeck.com/aluzzardi/heart-of-the-swarmkit-topology-management)

* [Heart of the SwarmKit: Store, Topology & Object Model](https://www.youtube.com/watch?v=EmePhjGnCXY)

* [Raft Consensus Visualization (Our Swarm DB and how it stays in sync across nodes)](http://thesecretlivesofdata.com/raft/)

## 59. Swarm Mode: Built-In Orchestration

* new commands:

```powershell
docker swarm 
docker node
docker service
docker stack
docker secret
```

* Manager Node: 
  1. API
    *  從client端接收command
    * 產生 service object
  2. Orchestrator
    * Reconciliation loop for service objects 
    * 產生 tasks
  3. Allocator 
    * Allocates IP addresses to tasks
  4. Scheduler
    * Assigns nodes to tasks
  5. Dispatcher
    * Checks in on workers
* Worker Node
  1. Worker
    * Connects to dispatcher to check on assigned tasks
  2. Executor 
    * Executes the tasks assigned to worker node 

## 60. Create Your First Service and Scale It Locally

* References: [Deploy services to a swarm](https://docs.docker.com/engine/swarm/services/)

* 確認 Swarm 的狀態, Swarm: inactive
```powershell
docker info 
```

* 開啟 Swarm
```powershell
docker swarm init 
```

* 提示
```powershell
Swarm initialized: current node (dej9tdo8lo3ggukfyrz0n8vwr) is now a manager.

To add a worker to this swarm, run the following command:

    docker swarm join --token SWMTKN-1-0jw57hk7cq1081o83cpinefc1mb0w2ch31qqhnlt5zcfesy1un-8c7op4sjb4v303zx3200carke 192.168.65.3:2377

To add a manager to this swarm, run 'docker swarm join-token manager' and follow the instructions.
```

* 列出 swarm 裡面的 nodes 
```powershell
docker node ls 
```

* service in swarm replace the docker run 


* 建立一個service, 會回傳一個 service ID, 此時 docker container ps 也會有一個在run的 container
```powershell
docker service create alpine ping 8.8.8.8 
```

* 列出 services 
```powershell
docker service ls 
```

* 列出 1個或多個service 內的 tasks/container
```powershell
docker service ps <SERVICE>
```

* update the attribute of service (ex: replica), 
執行完後, 再執行 "docker service ls" 及 "docker service ps <SERIVCE>" 可以看到變化, "docker container ps" 也可以看到變化
```powershell
docker service update <SERVICE>
docker service update <ID> --replicas 3
```

* "docker container update" 可以更新 containers 的 configurations, 
  但通常用"docker service update"?, 利用service管理, 只update/替換 某些container, 讓服務/網頁不中斷?

* 強制關掉某個 container, 再執行 "docker service ls" 可以看到 REPLICAS 變成 2/3, 但過不久又會再開一個, 變回 3/3
```powershell
docker container rm -f <CONTAINER>
docker service ls
```

* 觀看service詳細資訊可以看到 history
```powershell
docker service ps <SERVICE>
```

* 移除 1個或多個 service, 也會移除 container(但可能要等幾秒)
```powershell
docker service rm <SERVICE>
```

## 63. Create a 3-Node Swarm Cluster

* use multiple hosts/nodes/instances

* Host options:
  1. [Play-with-docker](https://labs.play-with-docker.com/)
  2. docker-machine + VirtualBox
  3. Digital Ocean + Docker install
  4. Roll your own docker machine: AWS, GCP, Azure, DigitalOcean
  
* [Install docker anywhere](https://get.docker.com/)

* docker machine, (create a machine, 需要安裝virtual box)
```powershell
docker-machine create <NODE> 
docker-machine ssh <NODE> // 進入該machine
docker-machine env <NODE>
```

* Digital Ocean 的話, 要產生 SSH key. [參考連結](https://www.digitalocean.com/docs/droplets/how-to/add-ssh-keys/)
* 用 Digital Ocean 裡面的 Droplets 服務
```powershell
ssh root at IPADDRESS # 連進去該台機器

# 執行這兩個指令來安裝docker
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh
```

```powershell
docker swarm init --advertise-addr <IP Address> # 在 node 1 執行 init 
docker swarm join --token <TOKEN> <HOST:PORT> # node 2 利用 join 加入
```

* worker 不能使用 "docker swarm" 的指令, manager 才可以

```powershell
docker node update --role manager <NODE> # 在 node1中 將 node2 設為 manager
```

```powershell
docker swarm join-token manager # 在 node1 執行, 取得已manager 為身份加入的 token
# 再把列印出的 command 貼到 node3 上去執行
```

```powershell
docker service create --replicas 3 alpine ping 8.8.8.8  # 在 node1 建立 service
```

```powershell
docker node ps # 當下跑的 node狀態
docker node ps <NODE> # 特定 node 的狀態
```

```powershell
docker service ps <SERIVCE> # 列出 service 的 task, 在各個node都可執行, 結果一樣
```

# Section 8: Swarm Basic Features and How to Use Them In Your Workflow

## 65. Scaling Out with Overlay Networking 

* '--driver overlay', swarm-wide bridge network where the containers across hosts
```powershell
# 建立 driver 為 overlay 的 network
docker network create --driver overlay mydrupal 
```

* 'docker network ls' 裡面 NAME 為 ingress 的 overlay network 是 swarm預設建立的

* 每個service 可以連接到多個 networks

* 建立新的 postgreSQL & drupal service, 指定 name, network
```powershell
docker service create --name <NAME> --network <NETWORK> -e POSTGRES_PASSWORD=xxxx postgres 

docker service create --name <NAME> --network <NETWORK> -p 80:80 drupal

docker service ps <SERVISE> # 建立完後看service
docker service inspect <SERIVCE> # service 詳細資訊
```

* 在 drupal 設定的時候, Database 的 Host 名稱是用 service 名稱

* 就算 drupal service 是在node 3上面跑, 但是 node1, node2, node3的IP都可以連到

## 66. Scaling Out with Routing Mesh

* References: [Use swarm mode routing mesh](https://docs.docker.com/engine/swarm/ingress/)

* Routing Mesh: Routes ingress packets for a Service to proper Task
  1. Container-to-container in a Overlay network (uses VIP)
  2. External traffic incoming to published ports (all nodes listen)


```powershell
docker service create --name search --replicas 3 -p 9200:9200 elasticsearch:2 # 建立 service 
docker service ps <SERVICE:search> # 觀看 service 在各node情形
curl localhost:9200  # 可以得到回傳的 json 資料
curl <IP ADDRESS>:9200 
```

* Load balancer 是在 OSI 第三層(TCP), 而非第四層(DNS)

* 如果想要在同個 server 相同 IP, 相同port跑不同 website可以用兩個方式解決
  1. Nginx or HAProxy or LB Proxy
  2. Docker EE, 內建 layer for web proxy (UCP/Docker Data Center, is a web interface), 可以就丟一個 DNS name 到 swarm service的 web config


## 68. Create A Multi-Service Multi-Node Web App

* GOTO: \udemy-docker-mastery\swarm-app-1

* 建立 1 volume, 2 networks, 5 services

* 使用 docker hub的 images, 這樣swarm就不需要data。在 production swarm裡面 不要去 build. 這不是 production swarm 通常該處理的事情。


```powershell
# 可以先清掉前面的 service 
docker service rm <SERVICE>

# 先建立 2個 network
docker network create -d overlay backend
docker network create -d overlay frontend

# 建立 vote service 
docker service create --name vote -p 80:80 --network frontend --replicas 2 bretfisher/examplevotingapp_vote

# 建立 redis service 
docker service create --name redis --network frontend --replicas 1 redis:3.2

# 建立 worker service
docker service create --name worker --network frontend --network backend bretfisher/examplevotingapp_worker:java

# 建立 db service and a volume
docker service create --name db --network backend -e POSTGRES_PASSWORD=xxxxx -e POSTGRES_HOST_AUTH_METHOD=trust --mount type=volume,source=db-data,target=/var/lib/postgresql/data postgres:9.4

# 建立 result service
docker service create --name result --network backend -p 5001:80 bretfisher/examplevotingapp_result

# 看一下建立的結果
docker service ls
docker service ps <SERVICE>
docker service logs <SERVICE>
```


## 70. Swarm Stacks and Production Grade Compose

* References: [NOT SUPPORTED FOR 'DOCKER STACK DEPLOY'](https://docs.docker.com/compose/compose-file/#not-supported-for-docker-stack-deploy)

* Production 環境只有一個host, 應該使用 docker-compose 還是 single node swarm?
  A: single-node swarm, [原因](https://github.com/BretFisher/ama/issues/8)

* Stacks 
  1. Production Grade Compose
  2. is a new layer of abstraction to swarm 
  3. accept __Compose files__ as their declarative definition for services, networks, and volumes

```powershell
docker stack deploy # 取代 docker service create
# stacks manager 會幫忙管理所有我們需要的 objects, 包含 overlay network
```

* 新的compose file關鍵字: __deploy:__, 而不是使用 'build:'

* docker-compose 會 忽略 __deploy__, swarm 會忽略 __build__

* swarm server 不需要 docker-compose CLI, 因為 docker compose 不是設計成 production tool。

* stack contains: services, volumes and overlay networks.
  And one service may have some tasks and each task is one container. See the image

* 68節建立service 的指令, 都可以改由 yml 來完成

* GOTO: \udemy-docker-mastery\swarm-stack-1\example-voting-app-stack.yml
  在node1 git clone 一份

* yml 的 version 至少要 3

* deploy 範例 
```powershell
docker stack deploy -c example-voting-app-stack.yml voteapp
# -c, Path to a Compose file 
```

* 其他指令
```powershell
docker stack ls # List stacks
docker stack ps <STACK> # List the tasks in the stack ex: <STACK>:voteapp
docker stack services <STACK> # List the services in the stack ex: <STACK>:voteapp

# 執行完後 再去 <IP>:5000, <IP>:5001 檢查

# 如果有更新, 再執行一次 docker stack deploy 會變成是 update 
docker stack deploy -c example-voting-app-stack.yml voteapp
```

## 71. Secrets Storage for Swarm: Protecting Your Environment Variables

* Easiest "secure" solution for storing secrets in Swarm. 
  1. version > 1.13
  2. only stored on disk on "Manager" nodes
  3. Secrets are first stored in Swarm, then assigned to Service(s)
  4. Only containers in assigned services can see them
  5. "look like" files in container but are actually in-memory file system
  6. use them by: /run/secrets/<secret_name> or /run/secrets/<secret_alias>

* Secret ex:
  - Usernames, passwords
  - TLS certificates and keys
  - SSH keys
  - any data prefer not ne "on front page of news"


## 72. Using Secrets in Swarm Services

* References: [Manage sensitive data with Docker secrets](https://docs.docker.com/engine/swarm/secrets/)

* GOTO: \udemy-docker-mastery\secrets-sample-1

* 在swarm裡面建立 secret有兩種方式
  1. 使用檔案
  2. 利用command line 傳進去 (STDIN)
  
* 建立 secrets
```powershell
# 1. 使用檔案, 資料存在txt file中
docker secret create psql_user psql_user.txt

# 2. 用 command line 
echo "xxxxxpwd" | docker secret create psql_pass - # "-": read from standard input 

# 第一種的缺點, 有存檔案在host中, 可能要用 remote API, 使用local電腦中的檔案
# 第二種的缺點, root user 可以看 logs  

docker secret ls # 列出 secrets
docker secret inspect <SECRET> # display secrets detailed information
```

* 使用 secrets
```powershell
docker service create --name psql --secret psql_user --secret psql_pass
-e POSTGRES_PASSWORD_FILE=/run/secrets/psql_pass -e POSTGRES_USER_FILE=/run/secrets/psql_user postgres
# --secret, Specify secrets to expose to the service, 指定此 service 可以使用那些 secret, 
# 然後用 /run/secrets/<SECRET_NAME> 的方式來存取 secret, how to use the secrets


docker exec -it <CONTAINER> <COMMAND:bash> # 進入 container bash
ls /run/secrets # 可以看到 psql_pass 和 psql_user 兩個 secret(像是檔案的方式呈現)

cat /run/secrets/psql_user # 可以看到裡面的值..., 看完再跳出

docker service update --secret-rm # remove the secrets, 執行這個會 re-deploy container, 所以不能 update password, update 的時候會 重開 container

```

## 73. Using Secrets with Swarm stacks

* References: [compose file-secrets configuration reference](https://docs.docker.com/compose/compose-file/#secrets-configuration-reference)

* GOTO: \udemy-docker-mastery\secrets-sample-2

```yaml
# docker-compose.yml
version: "3.1" # stack 要 3以上, stack + secrets 要 3.1 以上

services:
  psql:
    image: postgres
    secrets:
      - psql_user
      - psql_password
    environment:
      POSTGRES_PASSWORD_FILE: /run/secrets/psql_password
      POSTGRES_USER_FILE: /run/secrets/psql_user

secrets: # root secret key, define our secrets
  # 可以使用 file, 或是 事先建立好 secret, 然後在裡面使用
  # 用 external: 關鍵字, 可以看 此節 references
  psql_user:
    file: ./psql_user.txt # 跟 docker-compose.yml 同一層
  psql_password:
    file: ./psql_password.txt

```

```powershell
docker stack deploy -c docker-compose.yml sampleDB # deploy stack 的內容
# secret 的名稱會變為 sampleDB_psql_user, sampleDB_psql_password

# deploy 後, 應該要移除裡面的 secret 檔案?

docker stack rm sampleDB # 移除 stack, 也會移除 secret

```

* secret 相關疑慮問題與解答
 1. [Why is a Swarm Secret more secure than a clear text file?](https://github.com/BretFisher/ama/issues/86)
 2. [Is Docker secrets actually used in production scenarios?](https://github.com/BretFisher/ama/issues/35)
 3. [What security concerns should I have with Docker? How should I go about locking it down?](https://github.com/BretFisher/ama/issues/17)


## 74. Create A Stack with Secrets and Deploy

* GOTO: \udemy-docker-mastery\secrets-assignment-1

* 從 Docker\assignment\058-compose-assignment-2 修改 放到 \Docker\assignment\074-secrets-assignment-1

* docker-compose.yml 

```yaml
version: '3.1' # 修改為 3.1

services:
  drupal:
    image: drupal:8.8.2 # swarm 不build, 所以移除 build, 使用 official drupal image
    ports:
      - "8080:80"
    volumes:
      - drupal-modules:/var/www/html/modules
      - drupal-profiles:/var/www/html/profiles       
      - drupal-sites:/var/www/html/sites      
      - drupal-themes:/var/www/html/themes
  postgres:
    image: postgres:12.1
    environment:
      # - POSTGRES_PASSWORD=mypasswd # 改為使用 secret
      - POSTGRES_PASSWORD_FILE=/run/secrets/psql-pw
    secrets:
      - psql-pw # 表示此 service要使用此 secret
    volumes:
      - drupal-data:/var/lib/postgresql/data

volumes:
  drupal-modules:
  drupal-profiles:
  drupal-sites:
  drupal-themes:
  drupal-data:

# 新增加 secrets
secrets:
  psql-pw:
    extenal: true # 使用外部 secret, 需要先 command line create secret

```

```powershell
# 切到上面 docker-compose.yml 的路徑

# 先建立 secret 
echo "<STRING>" | docker secret create psql-pw -

# 在 deploy 
docker stack deploy -c docker-compose.yml drupal

# 查看stack 的 tasks執行狀況
docker stack ps drupal

```

# Section 9: Swarm App Lifecycle

## 76. Using Secrets With Local Docker Compose

* compose is not production tool, is design for development 

* 在 development 環境如果沒有swarm, 仍然可以使用同樣的 docker-compose.yml。也可以使用環境變數

```powershell
# 在相同的目錄 secrets-sample-2

docker-compose up -d

docker-compose exec psql cat /run/secrets/psql_user
# 仍然可以看到值, 但其實不是用 secret 的方式做
# 是在 background 用 -v argument 做 bind mount 
# 所以其實不安全, 只是為了 模擬 production environment 
# 只有 file based secret 可以, external 不行

```

## 77. Full App Lifecycle: Dev, Build, and Deploy With a Single Compose Design 

* References: 
  * [Share Compose configurations between files and projects-Multiple Compose files](https://docs.docker.com/compose/extends/#multiple-compose-files)
  * [Use Compose in production](https://docs.docker.com/compose/production/)


```powershell

docker-compose up # 在 local 的 development environment 使用

docker-compose up # 在 reomote 的 CI environment 使用, to do integration test 

docker stack deploy # 在 remote 的 production environment 使用, 

```

* GOTO: \udemy-docker-mastery\swarm-stack-3

1. docker-compose.yml 
  * default compose file
  * sets the defaults that are the same across all environments
2. docker-compose.override.yml
  * 當執行 "docker-compose up" 時, 自動帶入這個 override 的內容, 來取代 docker-compose.yml
3. docker-compose.prod.yml 
  * 要在 "docker-compose up -f" 明確使用這個檔案
  * 但在 production server 中, 沒有 docker-compose up 的指令, 所以要使用 docker-compose config 這個指令
4. docker-compose.test.yml
  * 要在 "docker-compose up -f" 明確使用這個檔案
  * 結合 CI solution (ex: Jenkins), 在每次commit code的時候, 去build image
  
```powershell

# 切到 \udemy-docker-mastery\swarm-stack-3 目錄下

docker-compose up # 執行此命令會先使用 docker-compose.yml, 然後在top 用 override.yml 覆蓋上去

docker-compose -f docker-compose.yml -f docker-compose.test.yml up -d # -f 的順序有差, base file 要在前面. 就會去使用 test 的設定

docker-compose -f docker-compose.yml -f docker-compose.prod.yml config # 會把兩個檔案結合起來成一個 compose file 

# 所以可以再輸出這個結合資訊到另一個檔案, 在 production 環境就是使用這個檔案

```

## 78. Service Updates: Changing Things In Flight

* References: [docker service update 指令](https://docs.docker.com/engine/reference/commandline/service_update/)


* 提供 service 中 tasks/containers 的 rolling replacement 
* limits downtime ("prevents" downtime 是 test 時候該做的, 不是 Orchestration 該處理的)
* 大部分的改變 (changes), 都會取代 containers
* 現在有 'scale' 和 'rollback' subcommand 可以更快取用
* 如果是執行 'stack deploy', 如果前一個版本存在, 那就是會當作 service update. 沒有 'stack update'


```powershell

# 更新 service 成新的 image 
docker service update --image <Image:version> <SERVICE>

# 新增環境變數 & 移除 port 
docker service update --env-add NODE_ENV=production --publish-rm 8080

# 同時改變多個 service 的 replicas 數量
docker service scale web=8 api=6

# 直接修改 yaml file, 然後再執行 stack deploy
docker stack deploy -c file.yml <STACK>

# 先建立一個 service 
docker service create -p 8088:80 --name web nginx:1.13.7

# 修改 replicas 數量
docker service scale web=5

# 修改 image 版本, 可以是舊版, 多個 replica 會一個一個修改
docker service update --image nginx:1.13.6 web

# 修改port, 需要同時 add 和 remove
docker service update --publish-rm 8088 --publish-dd 9090:80 web

# rebalance node (tips), 沒有更改任何東西, 但是強制執行 service update, 讓他重新分配 tasks 到 node上
docker service update --force web
```

## 79. Healthchecks in Dockerfiles

* References: 
  * [HEALTHCHECK in dockerfile](https://docs.docker.com/engine/reference/builder/#healthcheck)
  * [HEALTHCHECK in composefile](https://docs.docker.com/compose/compose-file/#healthcheck)

* Docker Healthchecks
  * 有支援 Dockerfile, compose yaml, docker run, swarm services
  * docker engine 會在 container 裡面 'exec' 指令
  * 預期的回傳是 exit 0 (OK) 或 exit 1 (Error)
  * 會有三種 states: starting, healthy, unhealthy
  * 並不是用來取代其他外部/第三方的 monitoring solution
  * 檢查 container basic level of healthy


```powershell

# 觀看 healthcheck status: docker container ls 

# 確認最近的5個 healthcheck: docker container inspect

# service will replace tasks if thay fail healthcheck

# service update 會等 healthcheck 結束才繼續

docker run \
  --health-cmd="curl -f localhost:9200/_cluster/health || false" \ # 為了回傳是 0/1
  --health-interval=5s \
  --health-retries=3 \
  --health-timeout=2s \
  --health-start-period=15s \
  elasticsearch:2

# 基本的使用預設選項的命令
HEALTHCHECK curl -f http://localhost/ || false

# 自行設定選項的命令
HEALTHCHECK --timeout=2s --interval=3s --retries=3 CMD curl -f http://localhost/ || exit 1  # exit 1 跟 false 一樣意思


```

```dockerfile

# Healthcheck in postgres Dockerfile

FROM postgres

HEALTHCHECK --interval=5s --timeout=3s \ 
  CMD pg_isready -U postgres || exit 1


```

```yaml
# Healthcheck in Compose/Stack Files
version: "2.1" # 至少要 2.1以上

services:
  web:
    image: nginx
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost"]
      interval: 1m30s
      timeout: 10s
      retries: 3
      start_period: 1m

```

```powershell
# run two containers, with and without healthcheck
docker container run --name p1 -d postgres

docker container run --name p2 -d --health-cmd="pg_isready -U postgres || exit 1" postgres

docker container ls

docker container inspect p2

# run two service, with and without healthcheck

docker service create --name p1 postgres

docker service create --name p2 --health-cmd="pg_isready -U postgres || exit 1" postgres

```

# Section 10: Container Registries: Image Storage and Distribution

## 81. Docker Hub: Digging Deeper

* Container Registries: 在 不是app server, 不是開發人員 workstations 的地方來存放 images

* 如果使用 GitHub or BitBucket 來放 code, 那不要直接按 "Create Repository". 也不要在 create 之前直接執行 "docker push". 選擇 AutomatedBuild. (現在好像直接整合在 "Create Repository" 裡面) 然後要連到 GitHub or BitBucket

* 如果有相依的 image, 可以設定 該image 的 links. 當該image 有變更的時候, 自己的image也會 rebuild. 

## 82. Understanding Docker Registry

* References: 
  * [Configuring a registry](https://docs.docker.com/registry/configuration/)
  * [Garbage collection](https://docs.docker.com/registry/garbage-collection/)
  * [Mirror(Registry as a pull through cache)](https://docs.docker.com/registry/recipes/mirror/)


* Docker Registry 
  * 不像 docker hub很多功能, 沒有 web UI, 只有簡單的 auth 系統
  * core: 用 Go 寫的 a web API 和 storage system
  * storage 支援: local, S3, Azure, Alibaba, Google Cloud 和 OpenStack Swift
  * Running Registry with 'TLS'

## 83. Run a Private Docker Registry

* "Secure by Default": docker won't talk to registry without HTTPS

```powershell

# 在 port 5000 跑 registry image 
docker container run -d -p 5000:5000 --name registry registry

# re-tag 現有的 image, 並 push 到 自己建立的新 registry
docker pull hello-world

docker tag hello-world 127.0.0.1:5000/helloworld

docker push 127.0.0.1:5000/helloworld

# 從 local cache 移除 image, 並再從新的 registry pull 下來

docker image rm hello-world

docker image rm 127.0.0.1:5000/helloworld

docker pull 127.0.0.1:5000/helloworld

# 重新建立 registry 並使用 bind mount, 看 registry 如何儲存 data

docker container kill registry

docker container rm registry

# GOTO: \udemy-docker-mastery\registry-sample-1

docker container run -d -p 5000:5000 --name registry -v ${pwd}\registry-data:/var/lib/registry registry 

docker push 127.0.0.1:5000/helloworld

```
## 84. Secure Docker Registry with TLS and Authentication 

