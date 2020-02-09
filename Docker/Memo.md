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



