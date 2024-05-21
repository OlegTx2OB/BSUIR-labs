package com.example.pexelsapiparody.service;

import com.example.pexelsapiparody.dto.CollectionDto;
import com.example.pexelsapiparody.model.Collection;
import org.springframework.data.domain.Page;

import java.util.List;

public interface CollectionService {

    List<CollectionDto> getAllCollections(int page, int perPage);

    CollectionDto getCollectionByName(String name);

    void createCollection(Collection collection, List<Long> photoIds);

    CollectionDto updateCollection(Long id, Collection collection, List<Long> photoIds);

    void deleteCollection(Long id);
}
