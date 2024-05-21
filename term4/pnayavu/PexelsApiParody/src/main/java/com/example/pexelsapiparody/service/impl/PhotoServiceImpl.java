package com.example.pexelsapiparody.service.impl;

import com.example.pexelsapiparody.dto.PhotoDto;
import com.example.pexelsapiparody.mapper.PhotoMapper;
import com.example.pexelsapiparody.model.Photo;
import com.example.pexelsapiparody.model.Source;
import com.example.pexelsapiparody.repository.PhotoRepository;
import com.example.pexelsapiparody.repository.SourceRepository;
import com.example.pexelsapiparody.service.PhotoService;
import jakarta.persistence.EntityNotFoundException;
import lombok.Getter;
import lombok.SneakyThrows;
import net.bytebuddy.implementation.bytecode.Throw;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;

import java.util.List;

@Getter
@Service
public class PhotoServiceImpl implements PhotoService {
    private final PhotoRepository mPhotoRepository;
    private final SourceRepository mSourceRepository;

    @Autowired
    public PhotoServiceImpl(
            PhotoRepository mPhotoRepository,
            SourceRepository mSourceRepository) {
        this.mPhotoRepository = mPhotoRepository;
        this.mSourceRepository = mSourceRepository;
    }

    @Override
    public List<PhotoDto> getAllPhotos(int page, int perPage) {
        PageRequest pageable = PageRequest.of(page, perPage);
        return PhotoMapper.toDtos(mPhotoRepository.findAll(pageable).getContent());
    }

    @SneakyThrows
    @Override
    public void createPhoto(Photo photo, Long sourceId) {
        photo.setSource(findSourceById(sourceId));
        mPhotoRepository.save(photo);
    }

    @Override
    public PhotoDto updatePhoto(Long id, Photo photo, Long sourceId) {
        photo.setSource(findSourceById(sourceId));
        photo.setId(id);
        return PhotoMapper.toDto(mPhotoRepository.save(photo));
    }

    @Override
    public void deletePhoto(Long id) {
        mPhotoRepository.deleteById(id);
    }

    private Source findSourceById(Long sourceId) {
        return mSourceRepository.findById(sourceId)
                .orElseThrow(() -> new EntityNotFoundException("Source with id " + sourceId + " not found"));
    }
}
