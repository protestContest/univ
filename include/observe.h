#pragma once

typedef void (*ObserveFn)(void *subject, void *ref);

void Observe(void *subject, ObserveFn update, void *ref);
void Unobserve(void *subject, ObserveFn update, void *ref);
void Notify(void *subject);
