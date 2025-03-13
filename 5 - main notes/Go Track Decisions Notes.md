**2025-03-07 19:29**
**Tags:** [go](../3%20-%20indexes/go.md)

## Go Track Decisions Notes

### Links Validation
1. **Initial validation using regular expressions.**
	I will assume the following possible link formats:
	`https://github.com/owner/repo`
	`https://stackoverflow.com/questions/*/`
	For the GitHub links: `https://github.com/[a-zA-Z0-0]+(?:-[a-zA-Z0-9]+)*/*`
	For the StackOverflow links: 
2. **The actual validation on the server side.**
	It will just simple `GET` request, e.g. `http.Get(url)` in order to check the existence of link.







## References