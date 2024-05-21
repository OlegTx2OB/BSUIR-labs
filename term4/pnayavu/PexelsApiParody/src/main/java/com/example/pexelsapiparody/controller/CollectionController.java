package com.example.pexelsapiparody.controller;

import com.example.pexelsapiparody.dto.CollectionDto;
import com.example.pexelsapiparody.model.Collection;
import com.example.pexelsapiparody.service.CollectionService;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Getter
@RestController
@RequestMapping("/collection")
public class CollectionController {
    private final CollectionService mCollectionService;

    @Autowired
    public CollectionController(CollectionService mCollectionService) {
        this.mCollectionService = mCollectionService;
    }

    @GetMapping("/all")
    public ResponseEntity<List<CollectionDto>> getAllCollections(
            @RequestParam(defaultValue = "0") int page,
            @RequestParam(defaultValue = "10") int perPage) {
        List<CollectionDto> collections = mCollectionService.getAllCollections(page, perPage);
        return ResponseEntity.ok(collections);
    }

    @GetMapping
    public ResponseEntity<CollectionDto> getCollectionByName(@RequestParam String query) {
        CollectionDto collection = mCollectionService.getCollectionByName(query);
        return new ResponseEntity<>(collection, HttpStatus.OK);
    }

    @PostMapping
    public ResponseEntity<Void> createCollection(
            @RequestBody Collection collection,
            @RequestParam(required = false) List<Long> photoIds
    ) {
        mCollectionService.createCollection(collection, photoIds);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @PutMapping("/{id}")
    public ResponseEntity<CollectionDto> updateCollection(
            @PathVariable("id") Long id,
            @RequestBody Collection collection,
            @RequestParam(required = false) List<Long> photoIds
    ) {
        CollectionDto updatedCollection = mCollectionService.updateCollection(id, collection, photoIds);
        return new ResponseEntity<>(updatedCollection, HttpStatus.OK);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteCollection(@PathVariable Long id) {
        mCollectionService.deleteCollection(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }
}
