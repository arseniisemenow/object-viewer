// Replace 'README.md' with the path to your Markdown file
const markdownFilePath = 'README.md';

fetch(markdownFilePath)
    .then(response => response.text())
    .then(markdown => {
        // Convert Markdown to HTML using a library like marked.js or showdown.js
        // For example, using marked.js:
        const html = marked(markdown);

        // Replace the content of the 'markdown-content' div with the generated HTML
        document.getElementById('markdown-content').innerHTML = html;
    })
    .catch(error => console.error('Error fetching Markdown file:', error));
