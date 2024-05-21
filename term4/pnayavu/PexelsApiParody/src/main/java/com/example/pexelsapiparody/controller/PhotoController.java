package com.example.pexelsapiparody.controller;

import com.example.pexelsapiparody.dto.PhotoDto;
import com.example.pexelsapiparody.model.Photo;
import com.example.pexelsapiparody.service.PhotoService;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Getter
@RestController
@RequestMapping("/photo")
public class PhotoController {
    private final PhotoService photoService;

    @Autowired
    public PhotoController(PhotoService photoService) {
        this.photoService = photoService;
    }

    @GetMapping
    public ResponseEntity<List<PhotoDto>> getAllPhotos(
            @RequestParam(defaultValue = "0") int page,
            @RequestParam(defaultValue = "10") int perPage) {
        List<PhotoDto> photos = photoService.getAllPhotos(page, perPage);
        return ResponseEntity.ok(photos);
    }

    @PostMapping
    public ResponseEntity<Void> createPhoto(
            @RequestBody Photo photo,
            @RequestParam(required = false) Long sourceId
    ) {
        photoService.createPhoto(photo, sourceId);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @PutMapping("/{id}")
    public ResponseEntity<PhotoDto> updatePhoto(
            @PathVariable("id") Long id,
            @RequestBody Photo photo,
            @RequestParam(required = false) Long sourceId
    ) {
        PhotoDto updatedPhoto = photoService.updatePhoto(id, photo, sourceId);
        return new ResponseEntity<>(updatedPhoto, HttpStatus.OK);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deletePhoto(@PathVariable Long id) {
        photoService.deletePhoto(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }
}
