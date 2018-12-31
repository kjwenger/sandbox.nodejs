#!/usr/bin/env node

const pdf = require('pdfjs-dist')

const url = process.argv[2];
pdf.getDocument(url).then(document => {
    document.getMetadata().then(metadata => {
        console.log(metadata)
    }).catch(err => {
        console.error('Error getting meta data', err)
    })
}).catch(err => {
    console.error('Error getting PDF from ' + url, err)
})