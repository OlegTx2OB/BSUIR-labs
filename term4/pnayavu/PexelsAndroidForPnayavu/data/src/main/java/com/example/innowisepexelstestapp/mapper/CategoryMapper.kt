package com.example.innowisepexelstestapp.mapper

import com.example.innowisepexelstestapp.dto.CategoryDto
import com.example.innowisepexelstestapp.model.Category

class CategoryMapper {

    fun toDto(c: Category): CategoryDto {
        return CategoryDto(c.name)
    }

    fun toModel(cDto: CategoryDto): Category {
        return Category(cDto.name, false)
    }

    fun toDtos(cList: List<Category>): List<CategoryDto> {
        val dtoList = mutableListOf<CategoryDto>()
        for (c in cList) {
            dtoList.add(toDto(c))
        }
        return dtoList
    }

    fun toModels(dtoList: List<CategoryDto>): List<Category> {
        val cList = mutableListOf<Category>()
        for (dto in dtoList) {
            cList.add(toModel(dto))
        }
        return cList
    }

}