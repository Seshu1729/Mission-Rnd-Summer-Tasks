# -*- coding: utf-8 -*-
# Generated by Django 1.9.6 on 2016-07-08 15:30
from __future__ import unicode_literals

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
        ('Todoist', '0002_auto_20160706_2016'),
    ]

    operations = [
        migrations.CreateModel(
            name='project',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('project_name', models.CharField(max_length=256)),
                ('created_user', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL)),
            ],
        ),
        migrations.CreateModel(
            name='target',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('target_name', models.CharField(max_length=256)),
                ('description', models.TextField(max_length=100000)),
                ('target_date', models.DateField()),
                ('status', models.BooleanField(default=False)),
                ('project_name', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='Todoist.project')),
            ],
        ),
        migrations.RemoveField(
            model_name='targets',
            name='target_name',
        ),
        migrations.DeleteModel(
            name='projects',
        ),
        migrations.DeleteModel(
            name='targets',
        ),
    ]