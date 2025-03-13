**2025-01-28 21:48**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md)

## RSS
The whole point of the `gator` program is to fetch the *RSS* feed of a website and store its content in a structured format in our database. That way we can display it nicely in our CLI.

RSS stands for "Really Simple Syndication" and is a way to get the latest content from a website in a structured format. If's fairly ubiquitous on the web: **most content sites as RSS feed**.

### Structure of an RSS feed
RSS is a specific structure of *XML* (gross). We will keep it simple and only worry about a few fields. Here's an example of the documents we'll parse:

```rss
<rss xmlns:atom="http://www.w3.org/2005/Atom" version="2.0">
<channel>
  <title>RSS Feed Example</title>
  <link>https://www.example.com</link>
  <description>This is an example RSS feed</description>
  <item>
    <title>First Article</title>
    <link>https://www.example.com/article1</link>
    <description>This is the content of the first article.</description>
    <pubDate>Mon, 06 Sep 2021 12:00:00 GMT</pubDate>
  </item>
  <item>
    <title>Second Article</title>
    <link>https://www.example.com/article2</link>
    <description>Here's the content of the second article.</description>
    <pubDate>Tue, 07 Sep 2021 14:30:00 GMT</pubDate>
  </item>
</channel>
</rss>
```

We'll then directly *unmarshal* this kind of document into structs like this:

```go
type RSSFeed struct {
	Channel struct {
		Title       string    `xml:"title"`
		Link        string    `xml:"link"`
		Description string    `xml:"description"`
		Item        []RSSItem `xml:"item"`
	} `xml:"channel"`
}

type RSSItem struct {
	Title       string `xml:"title"`
	Link        string `xml:"link"`
	Description string `xml:"description"`
	PubDate     string `xml:"pubDate"`
}
```

If there are any extra fields in the XML, the parser will just discard them, and if any are missing, the parser will leave them as their zero value.P




## References
[Boot.dev Blog Aggregator Tutorial](https://www.boot.dev/lessons/d049abb2-c733-4986-a33a-73f05e2ea06c)