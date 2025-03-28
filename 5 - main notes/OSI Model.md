**2025-03-15 15:53**
**Tags:** [networks](../2%20-%20tags/networks.md)

## OSI Model

![](../attachments/Pasted%20image%2020250315155408.png)

The OSI (Open Systems Interconnection) model is a conceptual framework used to understand and standardize the functions of telecommunication. It's divided into seven distinct layers, starting with the Physical Layer (Layer 1) at the bottom and ending with the Application Layer (Layer 7) at the top. When a message is sent, it moves from Layers 7 to Layer 1 on the sender's side and then travels from Layer 1 to Layer 7 on the receiver's side.

> [!NOTE]
> Shortcut to remember the OSI layers: Please Do Not Throw Sausage Pizza Away.

### Breakdown by OSI Layers

To understand each layer better, let's use a real-world analogy. Imagine two spy teams in enemy territory, each with four members. Team1 lives in House1, and Team2 lives in House2, which are located far apart. They use a secure messaging application to communicate.

### Application Layer

**Function:** This layer provides network services directly to the user. It's the interface where users interact with network application.
- **Example:** Team1 uses a secure messaging app to type out a critical message: "Meet at 7pm near Harbour." This is the layer where communication begins.
- **Message:** "Meet at 7pm near Harbour"

### Presentation Layer

**Function:** The presentation layer translates data between the application layer and the network format. It handles data encryption, decryption, compression, and translation.
- **Example:** The messaging app encrypts and compresses the message. For security, "Meet at 7pm near Harbour" is encrypted to "How are you?" to disguise its actual content and then compressed to make it smaller.
- **Encrypted Message:** "How are you?"

### Session Layer

**Function:** Manages sessions or connections between applications. It establishes, maintains, and terminates communication sessions.
- **Example:** The app creates a session between Team1 and Team2, ensuring secure communication. This session keeps the line open for acknowledgements and further messages, ensuring only authorized users (members of Team1) can send messages.
- **Session details:** A unique session ID track the conversation, the authentication verifies the sender's identity.

### Transport Layer

**Function:** This layer ensures complete data transfer by providing error checking, recovery, and flow control mechanisms. 
-  **Example:** The message "How are you?" is split into smaller segments if needed, each assigned a sequence number to ensure they are reassembled correctly. Team2 acknowledges receipt of each segment.
- **Segments:** "How", "are," "you?"
- **Port number:** Attached to each segment to direct it to the correct
 
### Network Layer

**Function:** The network layer manages the routing of data from the sender to the receiver. It determines the best path for data to travel.
- **Example:** Segments are put into packets with source and destination addresses. The app calculates the safest and most efficient route through enemy territory to avoid interception. In our analogy, this layer decides which house (destination) receives the message.
- **Packets:** Each segment is placed into packets with routing information.

### Data Link Layer

**Function:** Provides node-to-node data transfer and handles error detection and correction.
- **Example:** Packets are framed with error-checking codes to ensure error-free delivery. Each member of Team2 has their own mobile device, so the data link layer uses MAC addresses to deliver the message to the correct device.
- **Frames:** Packets are placed into frames with MAC addresses and error-checking codes.
- **Bits:** Converts data like "Hello" into bits (0s and 1s).

### Physical Layer

**Function:** This layer handles the transmission of raw bits over a physical medium. It includes hardware elements like cables, switches, and network cards.
- **Example:** Frames are converted into electrical, optical, or radio signals, depending on the medium used (e.g., a secure radio frequency or physical cable).
- **Signals:** The frames are transmitted as electrical, light, or radio signals.

## References
[OSI Model](https://nailyourinterview.org/interview-resources/computer-networks/osi-model)