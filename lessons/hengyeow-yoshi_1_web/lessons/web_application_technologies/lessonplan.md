# Web Application Technologies

## Table of Contents
0. [HTTP Protocol] (#http-protocol)
1. [URLs and HTTP Methods] (#urls-and-http-methods)
2. [Cookies] (#cookies)
3. [Status Codes] (#status-codes)
4. [HTTPS Protocol] (#https-protocol)
5. [Encoding Schemes] (#encoding-schemes)
6. [Resources] (#resources)

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

## URLs and HTTP Methods

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

## Cookies

Cookies are a key part of the HTTP protocol that most web applications use. They are often used in exploiting vulnerabilities. The cookie mechanism enables the server to send items of data to the client, which the client stores and resubmits to the server. 

Unlike the other types of request parameters (those within the URL query string or the message body), cookies continue to be resubmitted in each subsequent request without any particular action required by the application or the user.

![] (http://niyuj.com/wp-content/uploads/2016/05/C2GNfi.png)

A server issues a cookie using the `Set-Cookie` response header as shown below:

`Set-Cookie: tracking=tI8rk7joMx44S2Uu85nSWc`

The user’s browser then automatically adds the following header to subsequent requests back to the same server:

`Cookie: tracking=tI8rk7joMx44S2Uu85nSWc`

Cookies normally consist of a name/value pair, as shown, but they may consist of any string that does not contain a space. Multiple cookies can be issued by using multiple `Set-Cookie` headers in the server’s response. These are submitted back to the server in the same Cookie header, with a semicolon separating different individual cookies.

In addition to the cookie’s actual value, the `Set-Cookie` header can include any of the following optional attributes, which can be used to control how the browser handles the cookie:

 | Description
--- | ---
expires | sets a date until which the cookie is valid. If this attribute is not set, the cookie is used only in the current browser session.
domain | specifies the domain for which the cookie is valid. This must be the same or a parent of the domain from which the cookie is received.
path | specifies the URL path for which the cookie is valid.
secure | If this attribute is set, the cookie will be submitted only in HTTPS requests.
Http Only | If this attribute is set, the cookie cannot be directly accessed via client-side JavaScript.

## Status Codes
Each HTTP response message must contain a status code in its first line, indicating the result of the request. The status codes fall into five groups, according to the code’s first digit:

1. 1xx — Informational.
2. 2xx — The request was successful.
3. 3xx — The client is redirected to a different resource.
4. 4xx — The request contains an error of some kind.
5. 5xx — The server encountered an error fulfi lling the request.

There are numerous specific status codes, many of which are used only in specialized circumstances. Here are the status codes you are most likely to encounter when attacking a web application, along with the usual reason phrase associated with them: http://www.restapitutorial.com/httpstatuscodes.html

## HTTPS Protocol
The HTTP protocol uses plain TCP as its transport mechanism, which is unencrypted and therefore can be intercepted by an attacker who is suitably positioned on the network.

HTTPS is essentially the same application-layer protocol as HTTP but is tunneled over the secure transport mechanism, Secure Sockets
Layer (SSL). This protects the privacy and integrity of data passing over the network, reducing the possibilities for noninvasive interception attacks. HTTP requests and responses function in exactly the same way regardless of whether SSL is used for transport.

SSL is an excellent technology that protects the confidentiality and integrity of data in transit between the user’s browser and the web server. However, it does not stop attacks that directly target the server or client components of an application.

## Encoding Schemes

Web applications employ several different encoding schemes for their data.

### URL Encoding

URLs are permitted to contain only the printable characters in the US-ASCII character set — that is, those whose ASCII code is in the range 0x20 to 0x7e, inclusive.

The URL-encoding scheme is used to encode any problematic characters within the extended ASCII character set so that they can be safely transported over HTTP. The URL-encoded form of any character is the % prefix followed by the character’s two-digit ASCII code expressed in hexadecimal. You can find a reference list of URL encoding here: https://www.w3schools.com/tags/ref_urlencode.asp.

### Unicode Encoding

Unicode is a character encoding standard that is designed to support all of the world’s writing systems. In this case, we are interested in the UTF-8 encoding as it is what most websites use. UTF-8 is a variable-length encoding standard that employs one or more bytes to express each character. Detailed explanation of UTF-8 encoding can be found here: https://www.youtube.com/watch?v=vLBtrd9Ar28

For transmission over HTTP, the UTF-8-encoded form of a multibyte character simply uses each byte expressed in hexadecimal and
preceded by the % prefix:

E.g.
`%c2%a9 — ©`

### HTML Encoding 

HTML encoding is used to represent problematic characters so that they can be safely incorporated into an HTML document. Various characters have special meaning as metacharacters within HTML and are used to define a document’s structure rather than its content. To use these characters safely as part of the document’s content, it is necessary to HTML encode them.

Here is a quick reference to the HTML Symbol Entity Codes: http://www.entitycode.com/#direction-content

### Base64 Encoding

Base64 encoding allows any binary data to be safely represented using only printable ASCII characters. It is used for example to encode user credentials in basic HTTP authentication. Base64 encoding employs the following character set, which contains only printable ASCII characters:

`ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/`

If the final block of input data results in fewer than three chunks of outputdata, the output is padded with one or two `=` characters:

`SW50cm9kdWN0aW9uIHRvIFdlYiBTZWN1cml0eQ==`

### Hex Encoding

Many applications use straightforward hexadecimal encoding when transmitting binary data, using ASCII characters to represent the hexadecimal block. For example, hex-encoding the username `test` within a cookie would result in this:

`74657374`

## Resources

1. The Web Application Hacker's Handbook: Finding and Exploiting Security Flaws, 2nd Edition
2. [Basic concepts of web applications, how they work and the HTTP protocol] (https://www.youtube.com/watch?v=RsQ1tFLwldY)
3. [HTTP Methods: GET vs. POST] (https://www.w3schools.com/tags/ref_httpmethods.asp)
4. [Query string] (https://en.wikipedia.org/wiki/Query_string)
5. [Character encodings for beginners] (https://www.w3.org/International/questions/qa-what-is-encoding)


