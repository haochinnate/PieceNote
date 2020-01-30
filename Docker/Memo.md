### Section 2: The Best Way to Setup Docker for your OS   
> docker version 
(觀看 docker 版本)

> docker ps  
(查看目前執行的 containers)

> https://hub.docker.com/

> Windows 10 Pro/Enterprise -> Docker Desktop for Windows 


### Section 3: Creating and Using Containers Like a Boss

## 18. Check Our Docker Install and Config 

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

### Section 4: Container Images, Where to Find Them and How To Build Them

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

