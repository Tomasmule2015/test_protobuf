SRC_DIR='/home/mayh/桌面/我的任务/test_protobuf'
DST_DIR='/home/mayh/桌面/我的任务/test_protobuf' 

target:
	protoc -I $(SRC_DIR) --cpp_out=$(DST_DIR) $(SRC_DIR)/request.proto
	g++ request.pb.cc test_request.cpp -o read `pkg-config --cflags --libs protobuf` -lpthread

