FROM ubuntu:latest

# Set the working directory to /app
WORKDIR /app

# Copy project files to the container
COPY --link . .

# Install necessary tools including CMake
RUN apt-get update && \
    apt-get install -y git g++ make ca-certificates build-essential tar curl zip unzip pkg-config wget cmake

# Clone and bootstrap vcpkg
RUN wget -qO vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz && \
    mkdir -p ./opt/vcpkg && tar xf vcpkg.tar.gz --strip-components=1 -C ./opt/vcpkg && \
    ./opt/vcpkg/bootstrap-vcpkg.sh && \
    ln -s ./opt/vcpkg/vcpkg /usr/local/bin/vcpkg

# Install necessary libraries using vcpkg
RUN ./opt/vcpkg/vcpkg install boost-asio boost-system boost-thread boost-regex

# Create a build directory
RUN mkdir -p ./build

# Set the working directory to /app/build
WORKDIR /app/build

# Run CMake to configure the project
RUN cmake -DCMAKE_TOOLCHAIN_FILE=./opt/vcpkg/scripts/buildsystems/vcpkg.cmake ..

# Compile the project using make
RUN make

# Set the working directory back to the project root
WORKDIR /app

# Run the server when the container launches
CMD ["./build/serwerbin"]

