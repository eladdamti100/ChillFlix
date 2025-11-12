# Base image with GCC for building C++ projects
FROM gcc:latest

# Install required dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    git \
    build-essential \
    python3 \
    python3-pip

# Set the working directory in the container
WORKDIR /usr/src/Netflix

# Copy the 'src' directory into the container
COPY src /usr/src/Netflix/src

# Copy the 'data' directory into the container
COPY data /usr/src/Netflix/data

# Create a build directory
RUN mkdir build
WORKDIR /usr/src/Netflix/src

# Fetch dependencies, configure, and build the project
RUN cmake /usr/src/Netflix/src && make

# Default command to run the app executable (Netflix)
CMD ["./Netflix"]