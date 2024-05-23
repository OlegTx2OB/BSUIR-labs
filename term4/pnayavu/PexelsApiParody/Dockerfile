FROM openjdk:22
COPY target/PexelsApiParody-0.0.1-SNAPSHOT.jar PexelsApiParody-0.0.1-SNAPSHOT.jar
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
CMD ["java", "-jar", "PexelsApiParody-0.0.1-SNAPSHOT.jar"]