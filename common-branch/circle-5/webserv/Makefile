NAME		=	server
TEST		=	test

SRCS		=	src/main.cpp \
				src/ConfigParser/ConfigParser.cpp \
				src/Request/Request.cpp \
				src/RequestMap/RequestMap.cpp \
				src/MimeTypes/MimeTypes.cpp \
				src/AuthBasic/AuthBasic.cpp \
				src/Server/Server.cpp \
				src/Client/Client.cpp \
				src/CGI/CGI.cpp \
				src/utils.cpp \
				src/Response/Response.cpp \
				src/Error/Error.cpp

SRCS_TEST	=	src/__tests__/ConfigParser.test.cpp\
				src/__tests__/RequestMap.test.cpp\
				src/__tests__/Request.test.cpp\
				src/__tests__/MimeTypes.test.cpp\
				src/ConfigParser/ConfigParser.cpp\
				src/Client/Client.cpp\
				src/CGI/CGI.cpp \
				src/Request/Request.cpp\
				src/RequestMap/RequestMap.cpp \
				src/MimeTypes/MimeTypes.cpp \
				src/AuthBasic/AuthBasic.cpp \
				src/Response/Response.cpp \
				src/Server/Server.cpp \
				src/Error/Error.cpp \
				src/test-utils/test-utils.cpp\
				src/test-utils/main.cpp\
				src/utils.cpp

OBJS		=	$(SRCS:.cpp=.opp)
OBJS_TEST	=	$(SRCS_TEST:.cpp=.opp)

TMP_FILES   =	./tmp/*.tmp

CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $^ -o $@

$(TEST)		:	$(OBJS_TEST)
				$(CC) $(CFLAGS) $^ -o $@

%.opp		:	%.cpp
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				$(RM) $(OBJS) $(OBJS_TEST)
				$(RM) $(TMP_FILES)

fclean		:	clean
				$(RM) $(NAME) $(TEST)

re			:	fclean all
