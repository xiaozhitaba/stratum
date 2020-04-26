#
# Copyright 2019-present Open Networking Foundation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

FROM stratumproject/build:build as builder

RUN apt-get update && apt-get install -y --no-install-recommends \
    python \
    python-yaml \
    python-pip \
    libssl-dev \
    libelf-dev && \
    rm -rf /var/lib/apt/lists/*

ARG SDE_TAR
COPY $SDE_TAR /stratum/

ENV SDE /bf-sde
ENV SDE_INSTALL $SDE/install
RUN mkdir $SDE && tar xf /stratum/$SDE_TAR -C $SDE --strip-components 1

WORKDIR $SDE/p4studio_build

ARG JOBS=4
# Remove Thrift dependency from the profile (for SDE <= 8.9.x)
RUN sed -i.bak '/package_dependencies/d; /thrift/d' profiles/stratum_profile.yaml
RUN ./p4studio_build.py -up stratum_profile -wk -j$JOBS -shc && \
    rm -rf /var/lib/apt/lists/*

# Strip symbols from all .so files
RUN strip --strip-all $SDE_INSTALL/lib/*.so*

# Remove SDE and Linux headers tarball
RUN rm -r /stratum/*
