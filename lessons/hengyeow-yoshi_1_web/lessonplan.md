# Web Application Technologies

## Table of Contents
0. [HTTP Protocol] (#http-protocol)
1. [Encoding Schemes] (#encoding-schemes)

## HTTP Protocol
<!-- #![alt text] (https://github.com/tanhengyeow/lrn2lrn/blob/master/lessons/hengyeow-yoshi_1_web/src/http%20protocol.png ) -->
![] (https://www.ntu.edu.sg/home/ehchua/programming/webprogramming/images/HTTP.png)

The Hypertext transfer protocol (HTTP) is a common protocol used to access the World Wide Web and used by web applications. HTTP uses a message-based model in which a client sends a request message and the server returns a response message.

### HTTP Requests
![alt text] (https://github.com/tanhengyeow/lrn2lrn/blob/master/lessons/hengyeow-yoshi_1_web/src/http%20requests.png)

 | Description 
--- | --- 
First line of HTTP request separated by spaces | <ul><li>1. The HTTP method </li><li>2. The requested URL </li><li>3. The HTTP Version</li></ul>
Referer header | Shows the URL where the requested originated from (i.e. the user clicked a link on that page).
User-Agent header | Provides information about the browser or other client software that generated the request.
Host header | Specifies hostname that appeared in full URL being accessed.  
Cookie header | Used to submit additional parameters that server issued to the client.

### HTTP Responses
![alt text] (https://github.com/tanhengyeow/lrn2lrn/blob/master/lessons/hengyeow-yoshi_1_web/src/http%20responses.png)

 | Description 
--- | --- 
First line of HTTP response separated by spaces | <ul><li>1. The HTTP Version </li><li>2. A numeric status code indicating the result of the request. </li></ul>
Server header | Indicates the web server software/installed modules/server operating system.
Set-Cookie header | Issues the browser a further cookie. This cookie is submitted back in the Cookie header of subsequent requests to this server.
Pragma header | Instructs the browser not to store the response in its cache. 
Content-Type and Content-Length header | Indicates that the body of this message (in this case an HTML document) and the length of the message body in bytes.

### URLs

A uniform resource locator (URL) is a unique identifier for a web resource where resource can be retrieved. The format of most URLs is as follows:

`protocol://hostname[:port]/[path/]file[?param=value]`

Note that [?param=value] refers to the query string of the URL. A query string is the part of an URL containing data that does not fit into a hierarchical path structure. The query string commonly includes fields added to a base URL by a Web browser or other client application.

### HTTP Methods

The most commonly used HTTP methods for a request-response between a client and server are are `GET` and `POST`. 

#### The GET Method

The GET method is used to request data from a specified resource. The query string (name/value pairs) is sent in the URL of a GET request:

`/test/demo_form.php?name1=value1&name2=value2`

#### The POST Method 

The POST method is used to submit data to be processed to a specified resource. The query string (name/value pairs) is sent in the HTTP message body of a POST request:

`POST /test/demo_form.php`

`HTTP/1.1 Host: w3schools.com`

`name1=value1&name2=value2`

#### Other HTTP Methods

Method |	Description
--- | ---
HEAD	 | Same as GET but returns only HTTP headers and no document body
PUT	 | Uploads a representation of the specified URI
DELETE |	Deletes the specified resource
OPTIONS	| Returns the HTTP methods that the server supports
CONNECT	| Converts the request connection to a transparent TCP/IP tunnel

## Encoding Schemes
