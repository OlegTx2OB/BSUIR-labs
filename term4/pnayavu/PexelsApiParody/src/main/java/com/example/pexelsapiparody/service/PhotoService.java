package com.example.pexelsapiparody.service;

import com.example.pexelsapiparody.dto.PhotoDto;
import com.example.pexelsapiparody.model.Photo;

import java.util.List;

public interface PhotoService {
    List<PhotoDto> getAllPhotos(int page, int perPage);

    void createPhoto(Photo photo, Long sourceId);

    PhotoDto updatePhoto(Long id, Photo photo, Long sourceId);

    void deletePhoto(Long id);
}
