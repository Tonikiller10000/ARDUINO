# HaCEspSockets
An equivalent of windows socket in ESP(MCU) arduino environment. This library is an event driven with similar experience to windows socket. 

This library can also be implemented as a client or server depending on the use case of the user. The server socket can handle multiple client connection depending on the `HAC_SERVER_MAX_SOCKET_CLIENTS` definition(Note: Default value is 5 simultaneous client, it can be increase further but make sure to manage the memory it utilized for each session). 

- Events supported as a Server Socket:
1. `On Data Arrival`
    - Event raised when server receive a stream of data packet from the remote end client.
2. `On New Connection`
    - Event raised when server accepted a new connection from the remote end client.
3. `On Data Sent`
    - Event raised when server successfully send a data packet to the remote end client.
4. `On Socket Closed`
    - Event raised when server close or remote end client close the active connection.
5. `On Socket Error`
    - Event raised when server encounter a socket error on the existing connection to the remote end client.
6. `On Poll`
    - Event raised when server remote end client active connection is actively polling.

- Events supported as a Client Socket:
1. `On Data Arrival`
    - Event raised when client receive a stream of data packet from the remote end server.
2. `On Connected`
    - Event raised when client established a connection to remore end server.
3. `On Data Sent`
    - Event raised when client successfully send a data packet to the remote end server.
4. `On Socket Closed`
    - Event raised when server close or remote end client close the active connection.
5. `On Socket Error`
    - Event raised when client encounter a socket error on the existing connection to the remote end server.
6. `On Poll`
    - Event raised when client active connection is actively polling from the remote end server.

## Supported
> __Warning__ : This library work and tested on `ESP8266`. It will be tested for ESP32 on the future release.

## Dependency
> __Warning__ : Make sure to have the dependent library installed in your IDE before using this library.

1. ESP8266WiFi

## Installation
- Download: `https://github.com/SyntaxHarvy/HaCEspSockets/archive/refs/heads/main.zip`
- Arduino Ide:
1. Go to `Sketch` >> `Include Library` >> `Add` .zip library
2. Select the downloaded zip file.
OR
1. `Sketch` >> `Include Library` >> `Manage Libraries`
2. Type on the search input box `HaCEspSockets` and the relevant result will display the library with the installation instruction.
3. Press `install` button and select the `latest` released version.

- Others:
1. Unzip and modify the folder name to `HACEspSockets`
2. Move the modified folder on the designated library of the IDE you are using.

## How to use
> __Note__ : Please refer to any example of this library on the example section.

### Building an Application
Let us make a simple Socket server chat application with multiple client connection.

- #### Simple client server chat rule :
    - If a server receive a message `send_all` from any client, it will broadcast a word `[SERVER] I am    instructed to broadcast a message, how are you today?`.
    - If a server receive a message `close_all` from any client, it will broadcast a word `close`.
    - If a server receive a message `close` from any client, it will close the connection of the client that send the message.
    - If a client receive a message `close` from any client, it will close its connection to the server.

### Including the Library
Include the `HaCEspSockets` library to the header of the project. This will apply both to server and client application.

```cpp
#include <HaCEspSockets.h>
```

### Server Sketch
> __Note__  : Library should be added on the header(Refer to `Including the Library` step above).

- #### Debug
    - This will be useful if you want to see the different defined serial print debug on the library for tracing and troubleshootng purposes.     
    - Macro Definition 
        - > __Warning__ : Don't define this piece of code in your sketch header as these are defined already inside the library. However you may use this macro function in your sketch if you want to send any type of serial debug in your project.
    ```cpp
    /**
     * Debug simple messages
     * @param msg Message to be printed on the serial
     */
    DBG_CB_HSOC(msg)
    ```

    ```cpp
    /**
     * Debug simple messages
     * @param msg Message to be printed on the serial
     * @param ##__VA_ARGS__ argument
     */
    DBG_CB_HSOC2(msg, ...)
    ```

    - > __Warning__ : Make sure to write this piece of code before the library headers. 
    - > __Note__ : During production and if you want to disable the serial print debug then just comment out this piece of code in your main sketch program.   
    ```cpp
    #define HAC_ENABLE_DEBUG
    ```

- #### Instantiate the Library
    ```cpp
    HaCEspSockets haCSockets;
    ```

- #### Declaration of Callback Function Prototypes
    - Define the call back function for the `On Data Arrival` event.

    ```cpp
    /**
     * On Data Arrival Callback Function Prototype.
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     * @param buffer Data buffer receive by the server from the remote end client
     * @param packLen Data packet length
     * @param totalLen Buffer total length
     */
    void Server_clientOnDataArrival_CB(HaCClientInfo * clientInfo, const char* buffer, uint16_t packLen uint32_t totalLen);    
    ```

    - Define the call back function for the `On New Connection` event.

    ```cpp
    /**
     * On New Client Connection Callback Function Prototype.
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void Server_onNewClientConnection_CB(HaCClientInfo * clientInfo, std::vector<HaCClientInfo*> clientInfos);
    ```

    - Define the call back function for the `On Data Sent` event.

    ```cpp
    /**
     * On Data Sent Callback Function Prototype.
     * @param len Data packet length sent to the client
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     */
    void Server_clientOnDataSent_CB(uint16_t len, HaCClientInfo * clientInfo);
    ```

    - Define the call back function for the `On Socket Closed` event.

    ```cpp
    /**
     * On Socket Closed Callback Function Prototype.     
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void Server_clientOnSocketClosed_CB(HaCClientInfo * clientInfo, std::vector<HaCClientInfo*> clientInfos);
    ```

    - Define the call back function for the `On Socket Error` event.

    ```cpp
    /**
     * On Socket Error Callback Function Prototype.     
     * @param err Socket error for the associated client connection
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void Server_clientOnError_CB(uint32_t err, HaCClientInfo * clientInfo);
    ```

    - Define the call back function for the `On Poll` event.

    ```cpp
    /**
     * On Poll Callback Function Prototype.     
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void Server_clientOnPoll_CB(HaCClientInfo * clientInfo);
    ```

- #### Global Wifi Access Definition
    ```cpp
    /* #region Global Wifi Access Definition */
    const char* ssid = "MyIOTNetA";           //Change this to your correct wifi ssid
    const char* password =  "xtrp@ss143";     //Change this to your correct wifi password
    /* #endregion */ 
    ```

- #### Building the `setup` Function
    - Wifi typical initialization

    ```ccp
    /* #region Wifi typical initialization */
    Serial.begin(115200);  
    delay(1000);


    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        DBG_CB_HSOC("Connecting..");
    }
    DBG_CB_HSOC2("[Main] Connected to WiFi. IP: %s \n", WiFi.localIP().toString().c_str())
    /* #endregion */ 
    ```

    - HaCEspSockets events initialization

    ```ccp
    /* #region HaCEspSockets events initialization */
    haCSockets.Server_onNewClientConnection(Server_onNewClientConnection_CB);
    haCSockets.Server_clientOnDataArrival(Server_clientOnDataArrival_CB);
    haCSockets.Server_clientOnDataSent(Server_clientOnDataSent_CB);
    haCSockets.Server_clientOnSocketClosed(Server_clientOnSocketClosed_CB);
    haCSockets.Server_clientOnSocketError(Server_clientOnError_CB);
    haCSockets.Server_clientOnPoll(Server_clientOnPoll_CB);
    
    /* #endregion */ 
    ```

    - Setting up and starting the socket server

    ```ccp
    /* #region  Setting up and starting the socket server */
    haCSockets.setupServer(your_server_port);   //Server setup
    //haCSockets.setPingWatchdog(false);    // To Disable the ping watchdog
    haCSockets.startServer();       //Starting the server
    /* #endregion */ 
    ```

- #### Building the `loop` Function
    - > __Note__ : Loop function will be empty as the library is not loop dependent.

    ```ccp
    void loop() {}
    ```
- #### Definition of Callback Function Prototypes
    - `On Data Arrival` event callback logic breakdown.
        - Evalue the data receive:
            - If data = `close`, close the existing client connection.
            ```ccp
            if(strcmp(buffer, "close") == 0)    //If data receive is equal to close
            clientInfo->close();                //Close the existing client
            ```

            - If data = `send_all`, then server will broadcase a message `[SERVER] I am instructed to broadcast a message, how are you today?`.
            ```ccp
            if(strcmp(buffer, "send_all") == 0)    
            haCSockets.ServerBroadCast("[SERVER] I am instructed to broadcast a message, how are you today?");
            ```

            - If data = `close_all`, then server will broadcase a message `close`.
            ```ccp
            if(strcmp(buffer, "send_all") == 0)    
            haCSockets.ServerBroadCast("close");
            ```

    - Complete code for `On Data Arrival` event callback definition.
    ```ccp
    /**
        * On Data Arrival Callback Function.
        * @param clientInfo HaCClientInfo unique pointer for each client connection
        * @param buffer Data buffer receive by the server from the remote end client
        * @param packLen Data packet length
        * @param totalLen Buffer total length
        */
    void Server_clientOnDataArrival_CB(HaCClientInfo * clientInfo, 
        const char* buffer, uint16_t packLen, uint32_t totalLen)
    {

        DBG_CB_HSOC2("\n[Main] Incoming data from client connection id = %d", clientInfo->getConnectionId()); 
        DBG_CB_HSOC2("\n[Main] Data receive = %s", buffer);
        DBG_CB_HSOC2("\n[Main] Packet length = %d ", packLen);
        DBG_CB_HSOC2("\n[Main] Total Data length = %lu ", (unsigned long)totalLen);
        
        if(strcmp(buffer, "close") == 0)    
            clientInfo->close();
        if(strcmp(buffer, "send_all") == 0)    
            haCSockets.ServerBroadCast("Warning!Intruder detected, ink ink....");
        if(strcmp(buffer, "close_all") == 0)    
            haCSockets.ServerBroadCast("close");
    }    
    ```

    - Complete code for `On New Connection` event callback definition.
    ```ccp
    /**
        * On New Client Connection Callback Function.
        * @param clientInfo HaCClientInfo unique pointer for each client connection
        * @param clientInfos Array vectors of the HaCClientInfo connected to the server
        */
    void Server_onNewClientConnection_CB(HaCClientInfo * clientInfo, std::vector<HaCClientInfo*> clientInfos)
    {
    DBG_CB_HSOC2("\nNew Client with connection id = %d has been accepted..\n", clientInfo->getConnectionId());

    DBG_CB_HSOC("Active Connections \n");
    for(auto p : clientInfos)
        DBG_CB_HSOC2("\n[Main] Client with connection id = %d", p->getConnectionId());
    }
    ```

    - Complete code for `On Data Sent` event callback definition.
    ```ccp
    /**
        * On Data Sent Callback Function.
        * @param len Data packet length sent to the client
        * @param clientInfo HaCClientInfo unique pointer for each client connection
        */
    void Server_clientOnDataSent_CB(uint16_t len, HaCClientInfo * clientInfo)
    {
    DBG_CB_HSOC2("\n[Main] Sent to the client = %d with total length = %lu ..", clientInfo->getConnectionId(), (unsigned long)len);  
    }
    ```

    - Complete code for `On Socket Close` event callback definition.
    ```ccp
    /**
     * On Socket Closed Callback Function.     
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void Server_clientOnSocketClosed_CB(HaCClientInfo * clientInfo, std::vector<HaCClientInfo*> clientInfos)
    {
    DBG_CB_HSOC2("\n[Main] Client with connection id = %d has been closed \n", clientInfo->getConnectionId());

    DBG_CB_HSOC("Active Connections:");
    for(auto p : clientInfos)
        DBG_CB_HSOC2("\n[Main] Client with connection id = %d", p->getConnectionId());
    
    }
    ```

    - Complete code for `On Socket Error` event callback definition.
    ```ccp
    /**
        * On Data Arrival Callback Function.     
        * @param err Socket error for the associated client connection
        * @param clientInfos Array vectors of the HaCClientInfo connected to the server
        */
    void Server_clientOnError_CB(uint32_t err, HaCClientInfo * clientInfo)
    {
    DBG_CB_HSOC2("\n[Main] Client = %d, has error = %lu ..", clientInfo->getConnectionId(), (unsigned long)err);
    }
    ```

    - Complete code for `On Poll` event callback definition.
    ```ccp
    /**
        * On Poll Callback Function.     
        * @param clientInfos Array vectors of the HaCClientInfo connected to the server
        */
    void Server_clientOnPoll_CB(HaCClientInfo * clientInfo)
    {
    //DBG_CB_HSOC2("\n[Main] Client with connection id = %d is polling..", clientInfo->getConnectionId());
    }
    ```


### Client Sketch
> __Note__  : Library should be added on the header(Refer to `Including the Library` step above).

- #### Debug
    - This will be useful if you want to see the different defined serial print debug on the library for tracing and troubleshootng purposes.     
    - Macro Definition 
        - > __Warning__ : Don't define this piece of code in your sketch header as these are defined already inside the library. However you may use this macro function in your sketch if you want to send any type of serial debug in your project.
    ```cpp
    /**
     * Debug simple messages
     * @param msg Message to be printed on the serial
     */
    DBG_CB_HSOC(msg)
    ```

    ```cpp
    /**
     * Debug simple messages
     * @param msg Message to be printed on the serial
     * @param ##__VA_ARGS__ argument
     */
    DBG_CB_HSOC2(msg, ...)
    ```

    - > __Warning__ : Make sure to write this piece of code before the library headers. 
    - > __Note__ : During production and if you want to disable the serial print debug then just comment out this piece of code in your main sketch program.   
    ```cpp
    #define HAC_ENABLE_DEBUG
    ```

- #### Instantiate the Library
    ```cpp
    HaCEspSockets haCSockets;
    ```

- #### Declaration of Callback Function Prototypes
    - Define the call back function for the `On Data Arrival` event.

    ```cpp
    /**
     * On Data Arrival Callback Function Prototype.
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     * @param buffer Data buffer receive by the server from the remote end client
     * @param packLen Data packet length
     * @param totalLen Buffer total length
     */
    void clientOnDataArrival_CB(HaCClientInfo* clientInfo, 
    const char* buffer, uint16_t packetLength, uint32_t totalLength);    
    ```

    - Define the call back function for the `On Connected` event.

    ```cpp
    /**
     * On Connected Callback Function Prototype.
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void clientOnConnected_CB(HaCClientInfo * clientInfo);
    ```

    - Define the call back function for the `On Data Sent` event.

    ```cpp
    /**
     * On Data Sent Callback Function Prototype.
     * @param len Data packet length sent to the client
     * @param clientInfo HaCClientInfo unique pointer for each client connection
     */
    void clientOnDataSent_CB(uint16_t len, HaCClientInfo * clientInfo);
    ```

    - Define the call back function for the `On Socket Closed` event.

    ```cpp
    /**
     * On Socket Closed Callback Function Prototype.     
     * @param clientInfo HaCClientInfo unique pointer for each client connection     
     */    
    void clientOnSocketClosed_CB(HaCClientInfo * clientInfo);    
    ```

    - Define the call back function for the `On Socket Error` event.

    ```cpp
    /**
     * On Socket Error Callback Function Prototype.     
     * @param err Socket error for the associated client connection
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void clientOnSocketError_CB(uint32_t err, HaCClientInfo * clientInfo);
    ```

    - Define the call back function for the `On Poll` event.

    ```cpp
    /**
     * On Poll Callback Function Prototype.     
     * @param clientInfos Array vectors of the HaCClientInfo connected to the server
     */
    void clientOnPoll_CB(HaCClientInfo * clientInfo);
    ```
- #### Global Wifi Access Definition
    ```cpp
    /* #region Global Wifi Access Definition */
    const char* ssid = "MyIOTNetA";           //Change this to your correct wifi ssid
    const char* password =  "xtrp@ss143";     //Change this to your correct wifi password
    /* #endregion */ 
    ```

- #### Building the `setup` Function
    - Wifi typical initialization

    ```ccp
    /* #region Wifi typical initialization */
    Serial.begin(115200);  
    delay(1000);


    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        DBG_CB_HSOC("Connecting..");
    }
    DBG_CB_HSOC2("[Main] Connected to WiFi. IP: %s \n", WiFi.localIP().toString().c_str())
    /* #endregion */ 
    ```

    - HaCEspSockets events initialization

    ```ccp
    /* #region HaCEspSockets events initialization */
    haCSockets.clientOnDataArrival(clientOnDataArrival_CB);
    haCSockets.clientOnDataSent(clientOnDataSent_CB);
    haCSockets.clientOnSocketError(clientOnSocketError_CB);
    haCSockets.clientOnPoll(clientOnPoll_CB);
    haCSockets.clientOnSocketClosed(clientOnSocketClosed_CB);
    haCSockets.clientOnConnected(clientOnConnected_CB);
    //haCSockets.setPingWatchdog(false);    // To Disable the ping watchdog
    /* #endregion */ 
    ```

    - Setting up and connecting with the client socket

    ```ccp
    /* #region  Setting up and starting the socket server */
    haCSockets.setupClient(your_server_port, "your_server_ip");      //Setting up client socket, setupClient(port, remote ip)
    haCSockets.clientConnect();                     //Initiate connection to the server
    /* #endregion */ 
    ```
- #### Building the `loop` Function
    - > __Note__ : Loop function will be empty as the library is not loop dependent.

    ```ccp
    void loop() {}
    ```
- #### Definition of Callback Function Prototypes
    - `On Data Arrival` event callback logic breakdown.
        - Evalue the data receive:
            - If data = `close`, close the existing client connection.
            ```ccp
            if(strcmp(data, "close") == 0)  //If data receive is equal to close
            haCSockets.clientClose();     //Close the connection to the server
            ```

    - Complete code for `On Data Arrival` event callback definition.
    ```ccp
    /**
        * On Data Arrival Callback Function.
        * @param clientInfo HaCClientInfo unique pointer for each client connection
        * @param buffer Data buffer receive by the server from the remote end client
        * @param packLen Data packet length
        * @param totalLen Buffer total length
        */
    void clientOnDataArrival_CB(HaCClientInfo* clientInfo, const char* data, uint16_t packetLength, uint32_t totalLength)
    {
    char ip[50];
    memset(ip, 0, 50);
    clientInfo->getRemoteIP(ip);
    Serial.printf("\n[Main] Remote IP = %s ", &ip[0]);
    Serial.printf("\n[Main] Data receive = %s ", &data[0]);

    if(strcmp(data, "close") == 0)  //If data receive is equal to close
        haCSockets.clientClose();     //Close the connection to the server
    }
    ```

    - Complete code for `On Connected` event callback definition.
    ```ccp
    /**
        * On Connected Callback Function.
        * @param clientInfo HaCClientInfo unique pointer for each client connection
        */
    void clientOnConnected_CB(HaCClientInfo * clientInfo)
    {     
    char ip[50];
    memset(ip, 0, 50);
    clientInfo->getRemoteIP(ip);

    DBG_CB_HSOC2("\n[Main] Client is connected to remote ip = %s", &ip[0]);  
    haCSockets.clientSend("From client");
    }
    ```

    - Complete code for `On Data Sent` event callback definition.
    ```ccp
    /**
        * On Data Sent Callback Function Prototype.
        * @param len Data packet length sent to the client
        * @param clientInfo HaCClientInfo unique pointer for each client connection
        */
    void clientOnDataSent_CB(uint16_t len, HaCClientInfo * clientInfo)
    {
    char ip[50];
    memset(ip, 0, 50);
    clientInfo->getRemoteIP(ip);
    
    DBG_CB_HSOC2("\n[Main] Sent to the server = %s with total length = %lu ..", &ip[0], (unsigned long)len);  
    }
    ```

    - Complete code for `On Socket Closed` event callback definition.
    ```ccp
    /**
        * On Socket Closed Callback Function Prototype.     
        * @param clientInfo HaCClientInfo unique pointer for each client connection     
        */    
    void clientOnSocketClosed_CB(HaCClientInfo * clientInfo)
    {
    char ip[50];
    memset(ip, 0, 50);
    clientInfo->getRemoteIP(ip);

    DBG_CB_HSOC2("\n[Main] Client has been disconnected from remote ip = %s", &ip[0]);  
    }
    ```

    - Complete code for `On Socket Error` event callback definition.
    ```ccp
    /**
        * On Socket Error Callback Function Prototype.     
        * @param err Socket error for the associated client connection
        * @param clientInfos Array vectors of the HaCClientInfo connected to the server
        */
    void clientOnSocketError_CB(uint32_t err, HaCClientInfo * clientInfo)
    {
    char ip[50];
    memset(ip, 0, 50);
    clientInfo->getRemoteIP(ip);

    DBG_CB_HSOC2("\n[Main] Client connecting to remote ip = %s has an error = %lu ..", &ip[0], (unsigned long)err);  
    }
    ```

    - Complete code for `On Poll` event callback definition.
    ```ccp
    /**
        * On Poll Callback Function Prototype.     
        * @param clientInfos Array vectors of the HaCClientInfo connected to the server
        */
    void clientOnPoll_CB(HaCClientInfo * clientInfo)
    {
    //Take note that this event will be fire every 1 second once the connection to the server 
    //will be established
    char ip[50];
    memset(ip, 0, 50);
    clientInfo->getRemoteIP(ip);

    //DBG_CB_HSOC2("\nClient is polling from remote ip = %s", &ip[0]);  
    ```

## General Notes:
- > __Note__ 1 : The library has a default ping to the establised client connection in order to check the client/server connectivity. This is the handle that currently possible for the server or client to know if the client still connected or not(Close connection not caused by the normal close function, e.g the other end lost the connectivity without calling the close functions). With this functionality, both end it will keep receiving the message `ping` which corresponds to the watchdog message from the server or client. To disable this function, insert the code below on the setup of the application **after** calling the `setupServer()` or `setupClient()`.
    ```cpp
    haCSockets.setPingWatchdog(false);    // To Disable the ping watchdog
    ```

- Complete Example code can be extracted from the following
    - Arduino IDE
        - `File` >> `Examples` >> `HaCEspSockets` >> `Basic_Socket_Client_Chat_Application` , for client chat example.
        - `File` >> `Examples` >> `HaCEspSockets` >> `Basic_Socket_Server_Chat_Application` , for server chat example.
    - Direct from github
        - https://github.com/SyntaxHarvy/HaCEspSockets/blob/v0.1.1/examples/Basic_Socket_Client_Chat_Application/Basic_Socket_Client_Chat_Application.ino, for client chat example
        - https://github.com/SyntaxHarvy/HaCEspSockets/blob/v0.1.1/examples/Basic_Socket_Server_Chat_Application/Basic_Socket_Server_Chat_Application.ino, for server chat example

## Testing

Testing can be done by using putty.
- Download and install putty from its official website, https://www.putty.org/
- Run putty
- Select `Connection Type` to `raw`
- Type `your_server_ip` on `Host_Name`
- Type `your_server_port` on `Port`
- Click `Open`
- Once the CLI open, type anything you want to send to the server.
    - Test sending `send_all` to the server and the server should broadcast `[SERVER] I am    instructed to broadcast a message, how are you today?`
    - Test sending `close` to the server and your current putty connection should close its connection.
    - Testing sending `close_all` to the server and the server should broadcast `close` which will close the client chat socket running on other ESP8266 MCU.

    - ### Putty Screenshot
        <img width="964" alt="" src="https://github.com/SyntaxHarvy/HaCEspSockets/blob/main/images/00.PNG">  

        <img width="964" alt="" src="https://github.com/SyntaxHarvy/HaCEspSockets/blob/main/images/01.PNG">    
