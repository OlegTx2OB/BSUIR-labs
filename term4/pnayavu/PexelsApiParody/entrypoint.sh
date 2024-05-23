#!/bin/sh

# Wait for PostgreSQL to be ready
echo "Waiting for PostgreSQL to be ready..."
while ! curl http://db:5432 2>&1 | grep '52'; do
  sleep 0.1
done

echo "PostgreSQL is up - executing command"
exec "$@"