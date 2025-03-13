**2025-02-10 17:48**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md) [course](../2%20-%20tags/course.md)

## Ch 8. Webhooks
A webhook is just an event that's sent to your servery by an external service when something happens.
For example, here at Boot.dev we use Stripe as a third-part payment processor. When a student makes a payment, Stripe sends a webhook to the Boot.dev servers so that can unlock the student's membership.
1. Students makes a payment to stripe;
2. Stripe processes the payment;
3. If the payment is successful, Stripe sends an `HTTP POST` request to `https://api.bot.dev/stripe/webhook` (that's not the real URL, but you get the idea).

That's it! The only real difference between a webhook and a typical `HTTP` request is that the system making the request is an automated system, not a human loading a webpage or web app. As such, webhook handlers must be *idempotent* because the system on the other side may retry the request multiple times.

#### Idempo... What?
Idempotent, or "idempotence", is a fancy word that means "the same result no matter how many times you do it". For example, your typical `POST /api/chirps` (create a chirp) endpoint will *not* be idempotent. If you send the same request twice, you'll end up with two chirps with the same information but different IDs.

Webhooks, on the other hand, should be idempotent, and it's typically easy to build them this way because the client sends some kind of "event" and usually provides its own unique ID.

### Webhooks Review
A webhook is just an event that's sent to your server by an external service. There are just a couple of things to keep in mind when building a webhook handler:
- The third-party system will probably retry requests multiple times, so your handler should be *idempotent*.
- Be extra careful to never "acknowledge" a webhook request unless you processed it successfully. By sending a `2XX` code, you're telling the third-party system that you processed the request successfully, and they'll stop retrying it.
- When you're writing a server, you typically get to define the API. However, when you're integrating a webhook from a service like Stripe, you'll probably need to adhere to their API: they'll tell you what shape the events will be sent in.

## References
[Learn HTTP Servers in Go Ch 8.](https://www.boot.dev/lessons/1304e939-bf50-48d3-a351-b35faafc267d)