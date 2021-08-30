# Stream Upload Test Service

### Development
```
sudo docker run \
  -it \
  --name service --rm \
  -p 5002:5002 --net videos \
  -v /home/ermiry/Documents/ermiry/Projects/videos-server/stream-service:/home/stream \
  -v /home/ermiry/Documents/ermiry/Projects/videos-server/uploads:/home/uploads \
  -e RUNTIME=development \
  -e PORT=5002 \
  -e CERVER_RECEIVE_BUFFER_SIZE=4096 -e CERVER_TH_THREADS=4 \
  -e CERVER_CONNECTION_QUEUE=4 \
  -e MONGO_APP_NAME=stream -e MONGO_DB=videos \
  -e MONGO_URI=mongodb://stream:password@mongo:27017/videos \
  ermiry/stream-service:development /bin/bash
```

### Test
```
sudo docker run \
  -it \
  --name service --rm \
  -p 5002:5002 --net videos \
  -v /home/ermiry/Documents/ermiry/Projects/videos-server/uploads:/home/uploads \
  -e RUNTIME=test \
  -e PORT=5002 \
  -e CERVER_RECEIVE_BUFFER_SIZE=4096 -e CERVER_TH_THREADS=4 \
  -e CERVER_CONNECTION_QUEUE=4 \
  -e MONGO_APP_NAME=stream -e MONGO_DB=videos \
  -e MONGO_URI=mongodb://stream:password@mongo:27017/videos \
  ermiry/stream-service:test /bin/bash
```

## Routes

### Main

#### GET /api/stream
**Access:** Public \
**Description:** Stream service top level route \
**Returns:**
  - 200 on success

#### GET /api/stream/version
**Access:** Public \
**Description:** Returns stream service current version \
**Returns:**
  - 200 and version's json on success

### Videos

#### GET /api/stream/videos
**Access:** Public \
**Description:** Returns information of all existing videos \
**Returns:**
  - 200 on success

#### GET /api/stream/videos/:id/info
**Access:** Public \
**Description:** Returns information from a single video \
**Returns:**
  - 200 on success
  - 404 on video not found

#### GET /api/stream/videos/:id/image
**Access:** Public \
**Description:** Returns the video image \
**Returns:**
  - 200 on success
  - 404 on video not found

#### GET /api/stream/videos/:id/data
**Access:** Public \
**Description:** Returns actual chunks from the video file \
**Returns:**
  - 200 on success
  - 404 on video not found
