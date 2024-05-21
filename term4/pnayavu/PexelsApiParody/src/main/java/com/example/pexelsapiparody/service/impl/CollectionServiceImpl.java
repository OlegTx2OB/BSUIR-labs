package com.example.pexelsapiparody.service.impl;

import com.example.pexelsapiparody.dto.CollectionDto;
import com.example.pexelsapiparody.mapper.CollectionMapper;
import com.example.pexelsapiparody.model.Collection;
import com.example.pexelsapiparody.model.Photo;
import com.example.pexelsapiparody.repository.CollectionRepository;
import com.example.pexelsapiparody.repository.PhotoRepository;
import com.example.pexelsapiparody.service.CollectionService;
import jakarta.persistence.EntityNotFoundException;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Getter
@Service
public class CollectionServiceImpl implements CollectionService {
    private final CollectionRepository mCollectionRepository;
    private final PhotoRepository mPhotoRepository;

    @Autowired
    public CollectionServiceImpl(
            CollectionRepository mCollectionRepository,
            PhotoRepository mPhotoRepository) {
        this.mCollectionRepository = mCollectionRepository;
        this.mPhotoRepository = mPhotoRepository;
    }

    @Override
    public List<CollectionDto> getAllCollections(int page, int perPage) {
        PageRequest pageable = PageRequest.of(page, perPage);
        return CollectionMapper.toDtos(mCollectionRepository.findAll(pageable).getContent());
    }

    @Override
    public CollectionDto getCollectionByName(String name) {
        return CollectionMapper.toDto(mCollectionRepository.getCollectionByName(name));
    }

    @Override
    public void createCollection(Collection collection, List<Long> photoIds) {
        collection.setPhotos(findPhotosByIds(photoIds));
        mCollectionRepository.save(collection);
    }

    @Override
    public CollectionDto updateCollection(Long id, Collection collection, List<Long> photoIds) {
        collection.setId(id);
        collection.setPhotos(findPhotosByIds(photoIds));
        return CollectionMapper.toDto(mCollectionRepository.save(collection));
    }

    @Override
    public void deleteCollection(Long id) {
        mCollectionRepository.deleteById(id);
    }

    List<Photo> findPhotosByIds(List<Long> photoIds) {
        List<Photo> photos = new ArrayList<>();
        if (photoIds != null) {
            for (Long photoId : photoIds) {
                photos.add(mPhotoRepository.findById(photoId)
                        .orElseThrow(() -> new EntityNotFoundException("Photo with id " + photoId + " not found")));
            }
        }
        return photos;
    }
}
