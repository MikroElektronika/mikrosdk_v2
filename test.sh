#!/bin/bash
if [ -n "$(git status --porcelain changelog*)" ]; then
    echo "Updating with new changelog files";
else
    echo "No changes made to changelog files";
fi
