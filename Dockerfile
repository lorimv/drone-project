# for non M1/M2 mac users, use this FROM instruction
# FROM ubuntu:20.04

# for M1/M2 mac users, use this FROM instruction
FROM --platform=linux/amd64 ubuntu:20.04

# runs command and adds it to your image
RUN apt-get update && apt-get install -y \
  build-essential \  
  libssl-dev \
  zlib1g-dev

# 1 - make directory to contain all project files
RUN mkdir /project-files

# 2 - copy project code into newly created directory
COPY . /project-files

# 3 - CD into new directory for running container
WORKDIR /project-files

# 4 - compile code
RUN make -j

# 5 - run command in docker container once image ran
CMD ["./build/bin/transit_service",  "8081",  "apps/transit_service/web/"]