# -*- coding: utf-8 -*-
# Generated by Django 1.9.6 on 2016-07-06 14:46
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Todoist', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='projects',
            name='project_name',
            field=models.CharField(max_length=256),
        ),
        migrations.AlterField(
            model_name='targets',
            name='description',
            field=models.TextField(max_length=255),
        ),
    ]
