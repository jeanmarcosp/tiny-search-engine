# Tiny Search Engine Documentation

Authors:

- Jeanmarcos Perez

## Crawler

The TSE `Crawler` is a standalone program that crawls the web and retrieves webpages starting from a "seed" URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given "depth".

Usage: `./crawler seedURL pageDirectory maxDepth`

- where `seedURL` is an 'internal' directory, to be used as the initial URL,
- where `pageDirectory` is the (existing) directory in which to write downloaded webpages, and
- where `maxDepth` is an integer in range [0..10] indicating the maximum crawl depth.

## Indexer

The TSE `Indexer` is a standalone program that reads the document files produced by the TSE `Crawler`, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the `Indexer` and saves it to another file.

Usage: `./indexer pageDirectory indexFilename`

- where `pageDirectory` is the pathname of a directory produced by the `Crawler`, and
- where `indexFilename` is the pathname of a file into which the index should be written; the `Indexer` creates the file (if needed) and overwrites the file (if it already exists).

## Querier

The TSE `Querier` is a standalone program that reads the index file produced by the TSE `Indexer`, and page files produced by the TSE `Querier`, and answers search queries submitted via stdin.

Usage: `./querier pageDirectory indexFilename`

- where `pageDirectory` is the pathname of a directory produced by the `Crawler`
- where `indexFilename` is the pathname of a file produced by the `Indexer`

### Notes

- I made a read-only directory called `readOnlyDir` to use in test cases for `Indexer` which ask for a read-only directory and a read-only file.
