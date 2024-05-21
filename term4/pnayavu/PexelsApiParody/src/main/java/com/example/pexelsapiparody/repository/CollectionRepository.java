package com.example.pexelsapiparody.repository;

import com.example.pexelsapiparody.model.Collection;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface CollectionRepository extends JpaRepository<Collection, Long> {
    Collection getCollectionByName(String name);
}
