package com.example.pexelsapiparody.controller;

import com.example.pexelsapiparody.dto.SourceDto;
import com.example.pexelsapiparody.model.Source;
import com.example.pexelsapiparody.service.SourceService;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Getter
@RestController
@RequestMapping("/source")
public class SourceController {
    private final SourceService sourceService;

    @Autowired
    public SourceController(SourceService sourceService) {
        this.sourceService = sourceService;
    }

    @GetMapping
    public ResponseEntity<List<SourceDto>> getAllSources() {
        List<SourceDto> sources = sourceService.getAllSources();
        return ResponseEntity.ok(sources);
    }

    @PostMapping
    public ResponseEntity<Void> createSource(
            @RequestBody Source source) {
        sourceService.createSource(source);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @PutMapping("/{id}")
    public ResponseEntity<SourceDto> updateSource(
            @PathVariable("id") Long id,
            @RequestBody Source source) {
        SourceDto updatedSource = sourceService.updateSource(id, source);
        return new ResponseEntity<>(updatedSource, HttpStatus.OK);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteSource(@PathVariable Long id) {
        sourceService.deleteSource(id);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
}